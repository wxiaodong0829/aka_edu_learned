#include "common.h"
//求盘块的首地址
inline u32 blk_to_addr(void *fs, u16 blksz, u32 blkno)
{
	return (u32)fs + blksz * blkno;
}
//求第一个超级块的地址
// 缺陷：只能求第一个块组的超级块的首地址.
inline u32 super_base(void *fs)
{
	return (u32)fs + BLKSZ_1K;
}
//求块组描述符表盘块的地址
inline u32 grp0_base(void *fs, u16 blksz)
{
	// *(u32 *)(super_base(fs) + 20) 取出超级块中描述的第一个块组的起始盘块号 1
	return blk_to_addr(fs, blksz, (*(u32 *)(super_base(fs) + 20) + 1));
}
//根据块组描述符表盘块的地址并对应其中的内容计算出存放inode结构的起始盘块的地址
inline u32 grp0_itb_base(void *fs, u16 blksz)
{
	//*((u32 *)(grp0_base(fs, blksz) + 8)) 取出块租描述符表盘块中存放inode结构的起始盘块的盘块号
	return blk_to_addr(fs, blksz, *((u32 *)(grp0_base(fs, blksz) + 8)));
}
// 求出此inode结构盘块的第二(系统固定的存根文件)个inode结构的地址
inline u32 root_inode_base(void *fs, u16 blksz)
{
	return grp0_itb_base(fs, blksz) + ISZ;
}
// 根据inode结构的地址，找其中的index数组的首地址
inline u32* root_index(void *fs, u16 blksz)
{
	// 根据inode表查出表中index数组首地址离inode结构首地址的距离
	return (u32 *)(root_inode_base(fs, blksz) + 40);
}
