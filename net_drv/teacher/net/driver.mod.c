#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x1d426304, "struct_module" },
	{ 0x2cf190e3, "request_irq" },
	{ 0xde75b689, "set_irq_type" },
	{ 0xfcb961e6, "kfree_skb" },
	{ 0xe6c3ebb0, "__raw_writesw" },
	{ 0x10067a90, "__netif_schedule" },
	{ 0xe4d02c15, "netif_rx" },
	{ 0xba17c929, "eth_type_trans" },
	{ 0xaa13d05, "__raw_readsw" },
	{ 0xefacb988, "skb_put" },
	{ 0xfdea2ae2, "dev_alloc_skb" },
	{ 0x40a6f522, "__arm_ioremap" },
	{ 0x446f6a88, "ether_setup" },
	{ 0xf20dabd8, "free_irq" },
	{ 0xae523ee, "free_netdev" },
	{ 0x45a55ec8, "__iounmap" },
	{ 0x8c019310, "unregister_netdev" },
	{ 0x24cf7ff3, "register_netdev" },
	{ 0xe914e41e, "strcpy" },
	{ 0xea147363, "printk" },
	{ 0x23773a48, "alloc_etherdev_mq" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

