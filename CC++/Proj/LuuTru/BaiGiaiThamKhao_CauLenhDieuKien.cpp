#include <iostream>
using namespace std;

// Lưu ý:
// 1. Hàm chỉ nên nhận đối số từ bên ngoài -> tính toán -> trả về kết quả
//    Hàm không nên làm hết tất cả: nhập -> tính toán -> xuất
//    (Trừ khi đề bài yêu cầu thì phải làm, nếu không thì hàm chỉ nên thực hiện công việc tính toán)
// 2. Nên mô tả vài dòng trước khi viết hàm
// 3. Nên định nghĩa các hằng số (nếu có) trước khi viết hàm để tiện việc trả về

// Bài 1
// Hàm hoán vị 2 số nguyên cho trước
void hoanVi(int& x, int& y)
{
	int t = x;
	x = y;
	y = t;
}

// Hàm sắp xếp tăng dần 3 số nguyên a, b, c cho trước
void sapXepTangDan(int& a, int& b, int& c)
{
	if (!(a < b)) // if (a > b)
	{
		hoanVi(a, b);
	}

	if (!(a < c))
	{
		hoanVi(a, c);
	}

	if (!(b < c))
	{
		hoanVi(b, c);
	}
}

// Bài 2
// Hàm tìm và trả về số nhỏ nhất trong 4 số nguyên a, b, c, d cho trước
int timSoNhoNhat(int a, int b, int c, int d)
{
	int snn = a;
	if (b < snn)
	{
		snn = b;
	}
	if (c < snn)
	{
		snn = c;
	}
	if (d < snn)
	{
		snn = d;
	}

	return snn;
}

// Bài 3
// Hàm đổi và trả về ký tự tương ứng với ký tự c cho trước
char doiKyTu(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c = c + 32;
	}
	else
	{
		if (c >= 'a' && c <= 'z')
		{
			c = c - 32;
		}
	}

	return c;
}

// Bài 4
// Hàm tính và trả về số tiền đi taxi phải trả ứng với số km > 0 cho trước
#define GIA_1 15000
#define GIA_2 13500
#define GIA_3 11000
double tinhTienTaxi(int km)
{
	double sotien = 0;

	if (km == 1)
	{
		sotien = GIA_1;
	}
	else // km >= 2
	{
		if (km <= 5)
		{
			sotien = GIA_1 + (km - 1)*GIA_2;
		}
		else // km >= 6
		{
			sotien = GIA_1 + 4*GIA_2 + (km - 1 - 4)*GIA_3;
			
			if (km > 120)
			{
				sotien = sotien * 0.9;
			}
		}
	}

	return sotien;
}

// Cau 5
// Cách 1: Xếp loại và xuất kết quả ra màn hình (không nên)
//         Dùng các if độc lập nhau sẽ rất dài!
void xepLoaiHocSinh_Cach1(float toan, float ly, float hoa)
{
	float dtb = (toan + ly + hoa) / 3;

	if (dtb >= 9.0f)
	{
		cout << "Xuat sac" << endl;
	}
	
	if (dtb >= 8.0f && dtb < 9.0f)
	{
		cout << "Gioi" << endl;
	}

	if (dtb >= 6.5f && dtb < 8.0f)
	{
		cout << "Kha" << endl;
	}

	if (dtb >= 5.0f && dtb < 6.5f)
	{
		cout << "Trung binh" << endl;
	}

	if (dtb >= 3.5f && dtb < 5.0f)
	{
		cout << "Yeu" << endl;
	}
	
	if (dtb < 3.5f)
	{
		cout << "Kem" << endl;
	}
}

// Cách 2: Tương tự cách 1 nhưng dùng if else lồng nhau
//         Tốt hơn nhưng... cũng không nên xuất trực tiếp ra màn hình
void xepLoaiHocSinh_Cach2(float toan, float ly, float hoa)
{
	float dtb = (toan + ly + hoa) / 3;

	if (dtb >= 9.0f)
	{
		cout << "Xuat sac" << endl;
	}
	else // dtb < 9.0
	{
		if (dtb >= 8.0f)
		{
			cout << "Gioi" << endl;
		}
		else // dtb < 8.0
		{
			if (dtb >= 6.5f)
			{
				cout << "Kha" << endl;
			}
			else // dtb < 6.5
			{
				if (dtb >= 5.0f)
				{
					cout << "Trung binh" << endl;
				}
				else // dtb < 5.0
				{
					if (dtb >= 3.5f)
					{
						cout << "Yeu" << endl;
					}
					else // dtb < 3.5
					{
						cout << "Kem" << endl;
					}
				}
			}
		}
	}
}

// Cách 3: Tính toán và trả về các con số ứng với loại
//         1, 2, ... 6 ứng với Xuất sắc, Giỏi, ..., Kém
int xepLoaiHocSinh_Cach3(float toan, float ly, float hoa)
{
	float dtb = (toan + ly + hoa) / 3;
	int loai;

	if (dtb >= 9.0f)
	{
		loai = 1; // Xuất sắc
	}
	else // dtb < 9.0
	{
		if (dtb >= 8.0f)
		{
			loai = 2; // Giỏi
		}
		else // dtb < 8.0
		{
			if (dtb >= 6.5f)
			{
				loai = 3; // Khá
			}
			else // dtb < 6.5
			{
				if (dtb >= 5.0f)
				{
					loai = 4; // Trung bình
				}
				else // dtb < 5.0
				{
					if (dtb >= 3.5f)
					{
						loai = 5; // Yếu
					}
					else // dtb < 3.5
					{
						loai = 6; // Kém
					}
				}
			}
		}
	}

	return loai;
}

// Cách 4: Định nghĩa các hằng ký hiệu thể hiện loại và ngưỡng phân loại (nên làm nếu được!)
#define XUAT_SAC 1
#define NGUONG_XUAT_SAC 9.0f
#define GIOI 2
#define NGUONG_GIOI 8.0f
#define KHA 3
#define NGUONG_KHA 6.5f
#define TRUNG_BINH 4
#define NGUONG_TRUNG_BINH 5.0f
#define YEU 5
#define NGUONG_YEU 3.5f
#define KEM 6
int xepLoaiHocSinh_Cach4(float toan, float ly, float hoa)
{
	float dtb = (toan + ly + hoa) / 3;
	int loai;

	if (dtb >= NGUONG_XUAT_SAC)
	{
		loai = XUAT_SAC;
	}
	else // dtb < NGUONG_XUAT_SAC
	{
		if (dtb >= NGUONG_GIOI)
		{
			loai = GIOI;
		}
		else // dtb < NGUONG_GIOI
		{
			if (dtb >= NGUONG_KHA)
			{
				loai = KHA;
			}
			else // dtb < NGUONG_KHA
			{
				if (dtb >= NGUONG_TRUNG_BINH)
				{
					loai = TRUNG_BINH;
				}
				else // dtb < NGUONG_TRUNG_BINH
				{
					if (dtb >= NGUONG_YEU)
					{
						loai = YEU;
					}
					else // dtb < NGUONG_YEU
					{
						loai = KEM;
					}
				}
			}
		}
	}

	return loai;
}

// Bài 6
// Cách 1: Giải phương trình bậc 1 với a, b cho trước
//         và xuất kết quả ra màn hình
void giaiPhuongTrinhBac1_Cach1(float A, float B)
{
	// PT: Ax + B = 0
	if (A == 0)
	{
		// => PT: B = 0
		if (B == 0)
		{
			cout << "Phuong trinh da cho vo so nghiem" << endl;
		}
		else // B != 0
		{
			cout << "Phuong trinh da cho vo nghiem" << endl;
		}
	}
	else // A != 0
	{
		float x = -B / A;
		cout << "Phuong trinh da cho co nghiem x = " << x << endl;
	}
}

// Cách 2: Giải phương trình bậc 1 với a, b cho trước
//         và trả về số lượng nghiệm (cũng là số lượng giải pháp) và giá trị nghiệm (nếu có)
#define VO_SO_NGHIEM -1
#define VO_NGHIEM 0
#define MOT_NGHIEM 1
int giaiPhuongTrinhBac1_Cach2(float A, float B, float& x)
{
	int songhiem;

	// PT: Ax + B = 0
	if (A == 0)
	{
		// => PT: B = 0
		if (B == 0)
		{
			songhiem = VO_SO_NGHIEM;
		}
		else // B != 0
		{
			songhiem = VO_NGHIEM;
		}
	}
	else // A != 0
	{
		x = -B / A;
		songhiem = MOT_NGHIEM;
	}

	return songhiem;
}

// Bài 7
// Cách 1: Giải phương trình bậc 2 với A, B, C cho trước
//         và xuất kết quả ra màn hình
void giaiPhuongTrinhBac2_Cach1(float A, float B, float C)
{
	// PT: Ax^2 + Bx + C = 0
	if (A == 0)
	{
		// => PT: Bx + C = 0
		giaiPhuongTrinhBac1_Cach1(B, C);
	}
	else // A != 0
	{
		float delta = B*B - 4*A*C;
		if (delta < 0)
		{
			cout << "Phuong trinh da cho vo nghiem" << endl;
		}
		else // delta >= 0
		{
			if (delta == 0)
			{
				float x = -B / (2*A);
				cout << "Phuong trinh da cho co nghiem kep x1 = x2 = " << x << endl;
			}
			else // delta > 0
			{
				float x1 = (-B - sqrt(delta)) / (2*A);
				float x2 = (-B + sqrt(delta)) / (2*A);
				cout << "Phuong trinh da cho co 2 nghiem pb x1 = " << x1 << ", x2 = " << x2 << endl;
			}
		}	 
	}
}

// Cách 2a: Giải phương trình bậc 2 với A, B, C cho trước
//          và trả về số lượng nghiệm (nghiệm kép tính là 2) và giá trị nghiệm (nếu có)
#define HAI_NGHIEM 2
int giaiPhuongTrinhBac2_Cach2a(float A, float B, float C, float& x1, float& x2)
{
	int songhiem;
	// PT: Ax^2 + Bx + C = 0
	if (A == 0)
	{
		// => PT: Bx + C = 0
		songhiem = giaiPhuongTrinhBac1_Cach2(B, C, x1);
	}
	else // A != 0
	{
		float delta = B*B - 4*A*C;
		if (delta < 0)
		{
			songhiem = VO_NGHIEM;
		}
		else // delta >= 0
		{
			if (delta == 0)
			{
				x1 = x2 = -B / (2*A);
				songhiem = HAI_NGHIEM;
			}
			else // delta > 0
			{
				x1 = (-B - sqrt(delta)) / (2*A);
				x2 = (-B + sqrt(delta)) / (2*A);
				songhiem = HAI_NGHIEM;
			}
		}	 
	}

	return songhiem;
}

// Cách 2b: Giải phương trình bậc 2 với A, B, C cho trước
//          và trả về số lượng giải pháp (nghiệm kép chỉ tính là 1 do trùng) và giá trị nghiệm (nếu có)
#define HAI_NGHIEM 2
int giaiPhuongTrinhBac2_Cach2b(float A, float B, float C, float& x1, float& x2)
{
	int sogiaiphap;
	// PT: Ax^2 + Bx + C = 0
	if (A == 0)
	{
		// => PT: Bx + C = 0
		sogiaiphap = giaiPhuongTrinhBac1_Cach2(B, C, x1);
	}
	else // A != 0
	{
		float delta = B*B - 4*A*C;
		if (delta < 0)
		{
			sogiaiphap = VO_NGHIEM;
		}
		else // delta >= 0
		{
			if (delta == 0)
			{
				x1 = x2 = -B / (2*A);
				sogiaiphap = MOT_NGHIEM; // Khác cách 2a chỗ này!
			}
			else // delta > 0
			{
				x1 = (-B - sqrt(delta)) / (2*A);
				x2 = (-B + sqrt(delta)) / (2*A);
				sogiaiphap = HAI_NGHIEM;
			}
		}	 
	}

	return sogiaiphap;
}

// Bài 8
// Ax^3 + Bx^2 + Bx + A = 0
// <=> (x + 1)(Ax^2 + (B - A)x + A) = 0
// Cách 1: Giải phương trình bậc 3 đối xứng với A, B cho trước
//         và xuất kết quả ra màn hình
void giaiPhuongTrinhBac3DoiXung_Cach1(float A, float B)
{
	cout << "Phuong trinh da cho co nghiem x = -1" << endl;
	giaiPhuongTrinhBac2_Cach1(A, B - A, A);
}

// Cách 2a: Giải phương trình bậc 3 đối xứng với A, B cho trước
//          và trả về số lượng nghiệm (nghiệm trùng vẫn tính bình thường) và giá trị nghiệm (nếu có)
int giaiPhuongTrinhBac3DoiXung_Cach2a(float A, float B, float& x1, float& x2, float& x3)
{
	int songhiem;

	x1 = -1;
	songhiem = giaiPhuongTrinhBac2_Cach2a(A, B - A, A, x2, x3);
	if (songhiem != VO_SO_NGHIEM)
	{
		songhiem++; // cộng thêm 1 nghiệm là -1
	}

	return songhiem;
}

// Cách 2b: Giải phương trình bậc 3 đối xứng với A, B cho trước
//          và trả về số lượng giải pháp (nghiệm trùng chỉ tính là 1) và giá trị nghiệm (nếu có)
int giaiPhuongTrinhBac3DoiXung_Cach2b(float A, float B, float& x1, float& x2, float& x3)
{
	int songhiem;

	x1 = -1;
	songhiem = giaiPhuongTrinhBac2_Cach2b(A, B - A, A, x2, x3);

	switch (songhiem)
	{
	case VO_NGHIEM:
		songhiem++;		// chỉ tính nghiệm x1 = -1
		break; 
	case MOT_NGHIEM:
		if (x2 != x1)	// nếu nghiệm đó khác x1 = -1
		{
			songhiem++;	// thì mới tính
		}
		break;
	case HAI_NGHIEM:
		if (x2 != x1)
		{
			songhiem++;
		}
		if (x3 != x1)
		{
			songhiem++;
		}
		break;
	}

	return songhiem;
}
// Bài 9
// Hàm kiểm tra năm nm cho trước có phải là năm nhuận hay không
bool laNamNhuan(int nm)
{
	if (nm % 400 == 0 || (nm % 4 == 0 && nm % 100 != 0))
	{
		return true;
	}
	else
	{
		return false;
	}

	// <=> return (nm % 400 == 0 || (nm % 4 == 0 && nm % 100 != 0));
}

// Hàm trả về số ngày trong tháng th thuộc năm nm cho trước
int tinhSoNgayTrongThang(int th, int nm)
{
	int songay;

	switch (th)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12: songay = 31; break;
	case 4:
	case 6:
	case 9:
	case 11: songay = 30; break;
	case 2:
		if (laNamNhuan(nm))
		{
			songay = 29;
		}
		else
		{
			songay = 28;
		}
		break;
	}

	return songay;
}

// Hàm kiểm tra ngày ng/th/nm cho trước có phải là ngày hợp lệ
bool laNgayHopLe(int ng, int th, int nm)
{
	bool ketqua = true; // Giả sử ngày hợp lệ
	
	// Kiểm tra năm
	if (!(nm > 0 && th))
	{
		ketqua = false; // Ngày không còn hợp lệ nữa!
	}

	// Kiểm tra tháng
	if (!(th >= 1 && th <= 12))
	{
		ketqua = false; // Ngày không còn hợp lệ nữa!
	}

	// Kiểm tra ngày
	if (!(ng >= 1 && ng <= tinhSoNgayTrongThang(th, nm)))
	{
		ketqua = false; // Ngày không còn hợp lệ nữa!
	}

	return ketqua; // Trả về trạng thái cuối cùng...
}

// Bài 10
// Hàm tìm ngày hôm trước của một ngày ng/th/nm cho trước (đã hợp lệ)
void timNgayHomTruoc(int& ng, int& th, int& nm)
{
	ng--;
	if (ng == 0)
	{
		th--;
		if (th == 0)
		{
			th = 12;
			nm--;
		}

		ng = tinhSoNgayTrongThang(th, nm);
	}
}

// Bài 11
// Hàm tìm ngày hôm sau của một ngày ng/th/nm cho trước (đã hợp lệ)
void timNgayHomSau(int& ng, int& th, int& nm)
{
	ng++;
	if (ng > tinhSoNgayTrongThang(th, nm))
	{
		ng = 1;
		th++;
		if (th > 12)
		{
			th = 1;
			nm++;
		}
	}
}

// Bài 12
// Hàm tính và trả về số thứ tự ngày trong năm từ ngày ng/th/nm cho trước (đã hợp lệ)
int tinhSTTNgayTrongNam(int ng, int th, int nm)
{
	int stt = ng;
	
	for (int thang = 1; thang <= th - 1; thang++)
	{
		stt = stt + tinhSoNgayTrongThang(thang, nm);
	}
	
	return stt;
}

// Bài 13
// Hàm tính và trả về số thứ tự ngày so với ngày 1/1/1 từ ngày ng/th/nm cho trước (đã hợp lệ)
int tinhSTTNgay(int ng, int th, int nm)
{
	int stt = tinhSTTNgayTrongNam(ng, th, nm);
	
	stt = stt + 365 * (nm - 1);
	for (int nam = 1; nam <= nm - 1; nam++)
	{
		if (laNamNhuan(nam))
		{
			stt++;
		}
	}
	
	return stt;
}

// Bài 14
// Hàm tính và trả về thứ trong tuần của ngày ng/th/nm và thứ của ngày đầu năm cho trước
// Trả về 2, 3, ..., 7, 8 ứng với T2, T3, ..., T7, CN
int tinhThuTrongTuan(int ng, int th, int nm, int thu)
{
	int stt = tinhSTTNgayTrongNam(ng, th, nm);
	int songayle = (stt - 1) % 7;

	// C1. Khi cộng thêm số ngày lẻ thì xét nếu lớn hơn 8 thì trừ bớt 2
	// C2. Đổi thứ từ 2 -> 8 thành từ 0 -> 6 để dễ tính
	thu = thu - 2;

	// Cộng số ngày dư với thứ đầu năm để suy ra thứ hiện tại
	// Chia 7 lấy dư để kết quả từ 0 đến 6
	int ketqua = (thu + songayle) % 7;
	
	return ketqua + 2; // Cộng thêm 2 để đổi kết quả từ 0 -> 6 thành từ 2 -> 8
}

// Bài 15
// Hàm kiểm tra 3 cạnh a, b, c cho trước có tạo thành một tam giác hay không
bool laTamGiac(float a, float b, float c)
{
	if (a + b > c && a + c > b && b + c > a)
	{
		return true;
	}
	else
	{
		return false;
	}
	
	// <=> return (a + b > c && a + c > b && b + c > a);
}

// Bài 16
// Nếu được nên viết thêm hàm so sánh 2 số thực có bằng nhau không vì so sánh bằng giữa 2 số thực thường sai
#define EPSILON 0.0001f
bool bang(float x, float y)
{
	if (x - y > -EPSILON && x - y < EPSILON) // <=> if (fabs(x - y) < EPSILON)
	{
		return true;
	}
	else
	{
		return false;
	}

	// <=> return (x - y > -EPSILON && x - y < EPSILON);
}

// Cách 1: Hàm xác định và xuất kết quả ra màn hình loại của tam giác có 3 cạnh a, b, c cho trước
void xacDinhLoaiTamGiac_Cach1(float a, float b, float c)
{
	// if (bang(a, b) && bang(b, c))
	if (a == b && b == c)
	{
		cout << "=> Day la tam giac deu" << endl;
	}
	else
	{
		// if (bang(a, b) || bang(b, c) || bang(c, a))
		if (a == b || b == c || c == a)
		{
			// if (bang(a*a + b*b, c*c) || bang(b*b + c*c, a*a) || bang(c*c + a*a, b*b))
			if (a*a + b*b == c*c || b*b + c*c == a*a || c*c + a*a == b*b)
			{
				cout << "=> Day la tam giac vuong can" << endl;
			}
			else
			{
				cout << "=> Day la tam giac can" << endl;
			}
		}
		else
		{
			// if (bang(a*a + b*b, c*c) || bang(b*b + c*c, a*a) || bang(c*c + a*a, b*b))
			if (a*a + b*b == c*c || b*b + c*c == a*a || c*c + a*a == b*b)
			{
				cout << "=> Day la tam giac vuong" << endl;
			}
			else
			{
				cout << "=> Day la tam giac thuong" << endl;
			}
		}
	}
}

// Cách 2: Hàm xác định và trả về loại của tam giác có 3 cạnh a, b, c cho trước
#define TG_DEU 1
#define TG_CAN 2
#define TG_VUONG_CAN 3
#define TG_VUONG 4
#define TG_THUONG 5
int xacDinhLoaiTamGiac_Cach2(float a, float b, float c)
{
	int loai;

	// if (bang(a, b) && bang(b, c))
	if (a == b && b == c)
	{
		loai = TG_DEU;
	}
	else
	{
		// if (bang(a, b) || bang(b, c) || bang(c, a))
		if (a == b || b == c || c == a)
		{
			// if (bang(a*a + b*b, c*c) || bang(b*b + c*c, a*a) || bang(c*c + a*a, b*b))
			if (a*a + b*b == c*c || b*b + c*c == a*a || c*c + a*a == b*b)
			{
				loai = TG_VUONG_CAN;
			}
			else
			{
				loai = TG_CAN;
			}
		}
		else
		{
			// if (bang(a*a + b*b, c*c) || bang(b*b + c*c, a*a) || bang(c*c + a*a, b*b))
			if (a*a + b*b == c*c || b*b + c*c == a*a || c*c + a*a == b*b)
			{
				loai = TG_VUONG;
			}
			else
			{
				loai = TG_THUONG;
			}
		}
	}

	return loai;
}

void main()
{ 

}
