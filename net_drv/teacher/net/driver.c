#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h> /* struct net_device, free_netdev */
#include <linux/skbuff.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/etherdevice.h> /* alloc_etherdev */
#include "cs8900.h"

MODULE_AUTHOR("akaedu");
MODULE_DESCRIPTION("CS8900A net Driver");
MODULE_LICENSE("GPL");

struct net_device *cs8900_dev;
spinlock_t mylock;

/* CS8900 I/O Access Routines */
static inline void cs8900_write(struct net_device *dev, u16 regid, u16 value)
{
	//1.把cs8900内部寄存器的偏移值写入偏移为0xA的指针端口
	outw(regid, dev->base_addr + PP_Address);

	//2.把值写入偏移为0xC的数据端口
	outw(value, dev->base_addr + PP_Data);
}

static inline u16 cs8900_read(struct net_device *dev, u16 regid)
{
	//1.把cs8900内部寄存器的偏移值写入偏移为0xA的指针端口
	outw(regid, dev->base_addr + PP_Address);

	//2.把内部寄存器的值从偏移为0xC的数据端口中读出来
	return (inw(dev->base_addr + PP_Data));
}

static inline void cs8900_set(struct net_device *dev, u16 regid, u16 value)
{
	cs8900_write(dev, regid, (cs8900_read(dev, regid) | value));
}

//把数据从网卡上拷贝到内存中，接收数据时调用
static inline void cs8900_frame_read(struct net_device *dev, struct sk_buff *skb, u16 length)
{
	//insw(port, to, 次数)
	insw(dev->base_addr, skb_put(skb, length), (length+1)/2); 
}

//把数据从内存上拷贝到网卡上，发送数据时调用
static inline void cs8900_frame_write(struct net_device *dev, struct sk_buff *skb)
{
	//outsw(port, from, 次数)
	outsw(dev->base_addr, skb->data,  (skb->len+1)/2);
}

//中断上下文
void cs8900_recv(struct net_device *dev)
{
	volatile u16 status, length;
	struct sk_buff *skb;
	//判断是不是一次成功的接收事件
	status = cs8900_read(dev, PP_RxStatus);
	length = cs8900_read(dev, PP_RxLength);

	if(!(status & RxOK))
		return;
	
	skb = dev_alloc_skb(length+2);
	if(skb == NULL)
		return;

	skb_reserve(skb, 2); //数据包头部预留两个字节，让IP首部边界对齐。
	
	//执行skb_put函数下拉tail指针，并且拷贝硬件上的数据到内存上的sk_buff中。
	cs8900_frame_read(dev, skb, length);
	
	skb->dev = dev;
	skb->protocol = eth_type_trans(skb, dev);
	netif_rx(skb);
}

irqreturn_t cs8900_interrupt(int irq, void *dev_id)
{
	volatile u16 status;

	struct net_device *dev = (struct net_device *)dev_id;
	while((status = cs8900_read(dev, PP_ISQ)))
	{
		switch(RegNum(status))
		{
			case RxEvent:
				cs8900_recv(dev);
				break;
			case TxEvent:
				netif_wake_queue(dev);//唤醒发送队列，继续给我们下一个包
				break;
			case BufEvent:
				if(RegContent(status) & TxUnderrun)
					netif_wake_queue(dev);
				break;
		}
	}
	
	return IRQ_HANDLED;	
}

int cs8900_open(struct net_device *dev)
{
	//1.初始化硬件
	cs8900_set(dev, PP_RxCFG, RxOKiE | BufferCRC | CRCerroriE | RuntiE | ExtradataiE);
	cs8900_set(dev, PP_TxCFG, TxOKiE | Out_of_windowiE | JabberiE);
	cs8900_set(dev, PP_BufCFG, Rdy4TxiE | TxUnderruniE);
	cs8900_set(dev, PP_RxCTL, RxOKA | BroadcastA | IndividualA);
	cs8900_set(dev, PP_BusCTL, EnableIRQ);
	cs8900_set(dev, PP_LineCTL, SerRxON | SerTxON);
	
	//2.注册中断处理函数
	set_irq_type(dev->irq, IRQF_TRIGGER_RISING);
	if(request_irq(dev->irq, cs8900_interrupt, 0, "cs8900", (void *)dev))
	{
		printk("error register irq in CS8900\n");
		return -1;
	}

	//3.启动接口的传输队列
	netif_start_queue(dev);

	return 0;
}

int cs8900_stop(struct net_device *dev)
{
	//1.清除寄存器
	cs8900_write(dev, PP_RxCFG, 0);
	cs8900_write(dev, PP_TxCFG, 0);
	cs8900_write(dev, PP_BufCFG, 0);
	cs8900_write(dev, PP_RxCTL, 0);
	cs8900_write(dev, PP_BusCTL, 0);
	cs8900_write(dev, PP_LineCTL, 0);
	
	//2.注销中断
	free_irq(dev->irq, (void *)dev);

	//3.暂停接口的传输队列
	netif_stop_queue(dev);

	return 0;
}

//进程上下文，可能被中断事件打断
int cs8900_xmit(struct sk_buff *skb, struct net_device *dev)
{
	volatile u16 status;

	spin_lock_irq(&mylock);
	netif_stop_queue(dev);

	cs8900_write(dev, PP_TxCMD,  TxStart(After5));
	cs8900_write(dev, PP_TxLength, skb->len);

	status = cs8900_read(dev, PP_BusST);
	if(status & TxBidErr)
	{
		spin_unlock_irq(&mylock);
		printk("invalid length!\n");
		return -1;
	}

	if(!(status & Rdy4TxNOW))	
	{
		spin_unlock_irq(&mylock);
		printk("buffer is not free!\n");
		return -1;
	}

	//把数据从内存拷贝到网卡芯片上，以后网卡会自动发送
	cs8900_frame_write(dev, skb);
	spin_unlock_irq(&mylock);

	dev_kfree_skb(skb);

	return 0;	
}

int cs8900_init(struct net_device *dev) // register_netdev() 调用 
{
	int i;

	printk("My CS8900 Driver starts to work!\n");
	
	dev->open = cs8900_open;
	dev->stop = cs8900_stop;
	dev->hard_start_xmit = cs8900_xmit;
	
	ether_setup(dev);//初始化net_device结构体中其他的一些重要的成员

	dev->base_addr = (unsigned long)ioremap(0x19000000, 16);
	dev->irq = IRQ_EINT9;

	dev->if_port = IF_PORT_10BASET; //RJ-45
	
	//MAC地址自己指定,协议栈用的MAC地址
	dev->dev_addr[0] = 0x80;
	dev->dev_addr[1] = 0x12;
	dev->dev_addr[2] = 0x34;
	dev->dev_addr[3] = 0x56;
	dev->dev_addr[4] = 0x78;
	dev->dev_addr[5] = 0x9A;

	//判断网卡是不是CS8900A芯片
	if(cs8900_read(dev, PP_ProductID) != 0x630E)
	{
		printk("error! it's not a CS8900 chip!\n");
		return -1;
	}

	//往int_num寄存器里写0，表示网卡这一端使用INTRQ0来连接的CPU一端的EINT9
	cs8900_write(dev, PP_IntNum, 0);

	//把MAC地址写入到网卡芯片的PP_IA寄存器上，作地址过滤用
	for(i=0; i<6; i+=2)
	{
		cs8900_write(dev, PP_IA+i,// 由于寄存器是 16位的
			(dev->dev_addr[i] | dev->dev_addr[i+1]<<8));
	}

	return 0;
}

int __init akae_init(void)
{
	struct net_device *dev = alloc_etherdev(0);
	if(dev == NULL)
	{
		printk("alloc net_device error!\n");
		return -1;
	}
	cs8900_dev = dev;
	dev->init = cs8900_init;
	strcpy(dev->name, "eth%d"); //给网卡一个名字
	spin_lock_init(&mylock);

	return (register_netdev(dev));
}

void __exit akae_exit(void)
{
	unregister_netdev(cs8900_dev);
	iounmap((void *)(cs8900_dev->base_addr));
	free_netdev(cs8900_dev);

	return;
}

module_init(akae_init);
module_exit(akae_exit);
