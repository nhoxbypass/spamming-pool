/* halt.c
 *	Chuong trinh don gian de kiem tra xem Chuong trinh nguoi dung co chay hay khong
 *	
 *	Chi can thuc thi "syscall" ma tat He hieu danh
 *
 * 	NOTE: vi mot so ly do, user programs voi cau truc du lieu toan cuc 
 *	doi khi khong hoat dong tren moi truong Nachos. Vi the hay can than!
 *	Mot goi y la cap phat cau truc du lieu nhu la
 * 	tu dong hoa trong mot thu tuc procedure, nhung neu ban muon lam nhu vay, ban phai
 *	that can trong de cap phat stack lon vua du de giu bo tu dong hoa!
 */

#include "syscall.h"

int
main()
{
    Halt();
    /* not reached */
}
