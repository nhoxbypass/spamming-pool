#include <iostream>
using namespace std;

// Bài 1a
// Hàm kiểm tra một số nguyên dương n cho trước có phải là số nguyên tố hay không
bool laSoNguyenTo(int n)
{
	int souoc = 0;
	
	for (int i = 1; i <= n; i++)
	{
		if (n % i == 0)
		{
			souoc++;
		}
	}

	if (souoc == 2)
	{
		return true;
	}
	else
	{
		return false;
	}

	// <=> return (souoc == 2);
}

// Bài 1b
// Hàm kiểm tra một số nguyên dương n cho trước có phải là số hoàn hảo hay không
bool laSoHoanHao(int n)
{
	int tonguoc = 0;
	
	for (int i = 1; i < n; i++)
	{
		if (n % i == 0)
		{
			tonguoc = tonguoc + i;
		}
	}

	if (tonguoc == n)
	{
		return true;
	}
	else
	{
		return false;
	}

	// <=> return (tonguoc == n);
}

// Bài 1c
// Hàm kiểm tra một số nguyên dương n cho trước có phải là số chính phương hay không
#include <cmath> // <=> math.h
bool laSoChinhPhuong(int n)
{
	int can_n = (int)sqrt((float)n);
	
	if (can_n * can_n == n)
	{
		return true;
	}
	else
	{
		return false;
	}


	// <=> return (can_n * can_n == n);
}

// 1d
// Hàm tìm và trả về số đảo của một số nguyên dương n cho trước
int timSoDao(int n)
{
	int sodao = 0, dv;
	
	while (n != 0)
	{
		dv = n % 10;
		sodao = sodao * 10 + dv;
		n = n / 10;
	}

	return sodao;
}

// Hàm kiểm tra một số nguyên dương n cho trước có phải là số đối xứng hay không
bool laSoDoiXung(int n)
{
	if (n == timSoDao(n))
	{
		return true;
	}
	else
	{
		return false;
	}
	
	// <=> return (n == timSoDao(n));
}

// Bài 1e
// Hàm kiểm tra một số nguyên dương n cho trước có các chữ số tăng dần hay không
bool laSoCoChuSoTangDan(int n)
{
	int dv, dvt;
	
	// Cho trước dvt giá trị > 9
	// để chắc chắn rằng dv được lấy ra ở lần đầu tiên thỏa dt < dvt (tăng dần)
	dvt = 10;
	while (n != 0)
	{
		dv = n % 10;
		n = n / 10;

		// Kiem tra
		if (!(dv < dvt)) // Nếu không tăng dần
		{
			return false;// thì dừng và trả về sai
		}
		
		dvt = dv;
	}

	return true;
}

// Bài 1f
// Hàm kiểm ra một số nguyên dương n cho trước có phải là số chỉ toàn các chữ số lẻ
bool laSoToanChuSoLe(int n)
{
	int dv;
	
	while (n != 0)
	{
		dv = n % 10;
		n = n / 10;

		// Kiem tra
		if (!(dv % 2 != 0)) // Nếu dv không phải số lẻ
		{
			return false;	// thì dừng và trả về sai
		}
	}

	return true;
}

// Bài 2a
// Hàm tính và trả về tổng các chữ số lẻ của số nguyên dương n
int tinhTongCacChuSoLe(int n)
{
	int dv, tong = 0;

	while (n != 0)
	{
		dv = n % 10;
		n = n / 10;

		if (dv % 2 != 0)
		{
			tong = tong + dv;
		}
	}

	return tong;
}

// Bài 2b
// Hàm tính và trả về tổng các chữ số nguyên tố của số nguyên dương n
int tinhTongCacChuSoNguyenTo(int n)
{
	int dv, tong = 0;

	while (n != 0)
	{
		dv = n % 10;
		n = n / 10;

		if (dv == 2 || dv == 3 || dv == 5 || dv == 7)
		// <=> if (laSoNguyenTo(dv))	// Phải viết thêm hàm laSoNguyenTo
		{
			tong = tong + dv;
		}
	}

	return tong;
}

// Bài 2c
// Hàm tính và trả về tổng các chữ số chính phương của số nguyên dương n
int tinhTongCacChuSoChinhPhuong(int n)
{
	int dv, tong = 0;

	while (n != 0)
	{
		dv = n % 10;
		n = n / 10;

		if (dv == 1 || dv == 4 || dv == 9)
		// <=> if (laSoChinhPhuong(dv))	// Phải viết thêm hàm laSoChinhPhuong	
		{
			tong = tong + dv;
		}
	}

	return tong;
}

// Bài 3a
// Hàm tìm và trả về chữ số nhỏ nhất của số nguyên dương n
int timChuSoNhoNhat(int n)
{
	int dv, snn;

	// Cho trước dvt giá trị >= 9
	// để chắc chắn rằng dv được lấy ra ở lần đầu tiên luôn <= snn này
	snn = 9;
	while (n != 0)
	{
		dv = n % 10;
		n = n / 10;

		// Kiem tra
		if (dv < snn)
		{
			snn = dv;
		}
	}

	return snn;
}

// Bài 3b
// Hàm tìm và trả về chữ số lớn nhất của số nguyên dương n
int timChuSoLonNhat(int n)
{
	int dv, sln;

	// Cho trước dvt giá trị <= 0
	// để chắc chắn rằng dv được lấy ra ở lần đầu tiên luôn >= sln này
	sln = 0;
	while (n != 0)
	{
		dv = n % 10;
		n = n / 10;

		// Kiem tra
		if (dv > sln)
		{
			sln = dv;
		}
	}

	return sln;
}

// Bài 4a
// Hàm tính và trả về ước số chung lớn nhất của 2 số nguyên dương a và b cho trước
int timUSCLN(int a, int b)
{
	while (a != b)
	{
		if (a > b)
		{
			a = a - b;
		}
		else
		{
			b = b - a;
		}
	}

	return a;
}

// Bài 4b
// Hàm tính và trả về bội số chung nhỏ nhất của 2 số nguyên dương a và b cho trước
int timBSCNN(int a, int b)
{
	return a * b / timUSCLN(a, b);	// Phải viết hàm timUSCLN trước
}

// Bài 5
// Fibo(0) = Fibo(1) = 1
// Fibo(n >= 2) = Fibo(n - 1) + Fibo(n - 2)
int Fibo(int n)
{
	if (n == 0 || n == 1)
	{
		return 1;
	}

	// n >= 2
	int a = 1, b = 1, c;
	// a b c
	//   a b c
	//     a b c
	for (int i = 2; i <= n; i++)
	{
		c = b + a;
		a = b;
		b = c;
	}

	return c;
}

// Bài 6a
// Hàm xuất ra màn hình các số nguyên tố không lớn hơn số nguyên dương n cho trước
void xuatSoNguyenTo(int n)
{
	cout << "Cac so nguyen to khong lon hon " << n << " la: ";
	for (int i = 2; i <= n; i++)
	{
		if (laSoNguyenTo(i))
		{
			cout << i << " ";
		}
	}
}

// Bài 6b
// Hàm xuất ra màn hình các thừa số nguyên tố của số nguyên dương n cho trước
void xuatCacThuaSoNguyenTo(int n)
{
	cout << "Cac thua so nguyen to cua " << n << " la: ";
	int i = 2;
	while (n > 1)
	{
		if (n % i == 0)
		{
			cout << i << " ";

			while (n % i == 0)
			{
				n = n / i;
			}
		}
		i++;
	}
}

// Bài 6c
// Hàm xuất ra màn hình các chữ số của số nguyên dương n cho trước từ phải sang trái 
void xuatCacChuSoTuPhaiSangTrai(int n)
{
	int dv;

	cout << "Cac chu so cua " << n << " tu phai sang trai la: ";
	while (n != 0)
	{
		dv = n % 10;
		n = n / 10;
		
		cout << dv << " ";
	}
}

// Bài 6d
// Hàm xuất ra màn hình các chữ số của số nguyên dương n cho trước từ phải sang trái 
void xuatCacChuSoTuTraiSangPhai(int n)
{
	int dv, dem;

	cout << "Cac chu so cua " << n << " tu phai sang trai la: ";

	// Đếm số lượng chữ số 0 ở bên phải
	dem = 0;
	while (n % 10 == 0)	// Trong khi chữ số đơn vị là 0
	{
		dem++;			// Ghi nhận
		n = n / 10;		// Bỏ số 0 đó đi
	}

	n = timSoDao(n);	// Phải viết hàm timSoDao
	
	// Xuất các chữ số của số đảo từ phải sang trái (giống bài 6c)
	// Có thể gọi hàm xuatCacChuSoTuPhaiSangTrai(n); nếu đã viết
	while (n != 0)
	{
		dv = n % 10;
		n = n / 10;
		
		cout << dv << " ";
	}

	// Xuất các số 0 đã ghi nhận
	for (int i = 1; i <= dem; i++)
	{
		cout << "0 ";
	}
}

// Bài 6e
// Hàm xuất n số chính phương đầu tiên nhưng chỉ dùng phép +
// 0 1 4 9 16 25 36 ...
// Nhận xét:
// - Giả sử đã có (i - 1)^2
// - Cần tính i^2 từ (i - 1)^2
// - Ta thấy: i^2 - (i - 1)^2 = (i - i + 1)(i + i - 1)
//                            = (i + i + (-1))
// Vậy muốn tính i^2 từ (i - 1)^2 trước đó ta cộng thêm một lượng i + i + (-1) 
void xuatCacSoChinhPhuong(int n)
{
	int i_mu_2 = 0;	// Số chính phương đầu tiên bằng 0

	cout << n << " so chinh phuong dau tien la: 0 ";

	for (int i = 1; i < n; i++) // 0^2 1^2 2^2 ... (n - 1)^2
	{
		i_mu_2 = i_mu_2 + i + i + (-1);
		cout << i_mu_2 << " ";
	}
}

// Bài 7
// Hàm tính và trả về q = a / d và r = a % d với a >= 0 và d > 0 cho trước (không dùng / và %)
void tinhThuongVaSoDu(int a, int d, int& q, int& r)
{
	q = 0;
	while (a >= d)
	{
		a = a - d;
		q++;
	}
	r = a;
}

// Bài 8
// Xuất các phương án đổi Nd từ các tờ 1d, 2d, 5d
// Cách 1
void doiTien_Cach1(int N)
{
	int soto1d, soto2d, soto5d;	// Số tờ mệnh giá 1d, 2d, 5d
	cout << "Cac phuong an doi " << N << "d la: " << endl;

	for (soto1d = 0; soto1d <= N / 1; soto1d++)
	{
		for (soto2d = 0; soto2d <= (N - soto1d * 1) / 2; soto2d++)
		// Hoac nhu sau cung duoc!: for (soto2d = 0; soto2d <= N / 2; soto2d++)
		{
			for (soto5d = 0; soto5d <= (N - soto1d * 1 - soto2d * 2) / 5; soto5d++)
			// Hoac nhu sau cung duoc!: for (soto5d = 0; soto5d <= N / 5; soto5d++)
			{
				if (soto1d * 1 + soto2d * 2 + soto5d * 5 == N)
				{
					cout << soto1d << " to 1d + ";
					cout << soto2d << " to 2d + ";
					cout << soto5d << " to 5d" << endl;
				}
			}
		}
	}
}

// Cách 2
#define MENH_GIA_1 1
#define MENH_GIA_2 2
#define MENH_GIA_3 5
void doiTien_Cach2(int N)
{
	int sotomg1, sotomg2, sotomg3;	// Số tờ mệnh giá 1, 2, 3
	cout << "Cac phuong an doi " << N << "d la: " << endl;

	for (sotomg1 = 0; sotomg1 <= N / MENH_GIA_1; sotomg1++)
	{
		for (sotomg2 = 0; sotomg2 <= (N - sotomg1 * MENH_GIA_1) / MENH_GIA_2; sotomg2++)
		// Hoac nhu sau cung duoc!: for (sotomg2 = 0; sotomg2 <= N / MENH_GIA_2; sotomg2++)
		{
			for (sotomg3 = 0; sotomg3 <= (N - sotomg1 * MENH_GIA_1 - sotomg2 * MENH_GIA_2) / MENH_GIA_3; sotomg3++)
			// Hoac nhu sau cung duoc!: for (sotomg3 = 0; sotomg3 <= N / MENH_GIA_3; sotomg3++)
			{
				if (sotomg1 * MENH_GIA_1 + sotomg2 * MENH_GIA_2 + sotomg3 * MENH_GIA_3 == N)
				{
					cout << sotomg1 << " to " << MENH_GIA_1 << "d + ";
					cout << sotomg2 << " to " << MENH_GIA_2 << "d + ";
					cout << sotomg3 << " to " << MENH_GIA_3 << "d" << endl;
				}
			}
		}
	}
}

// Cách 3: Giống cách 1 và 2 nhưng không sử dụng vòng lặp for thứ 3 mà chỉ cần kiểm tra số tiền còn lại có chia hết cho MENH_GIA_3 hay không?

// Bài 9
int tinhGiaTri9a(int n) // n > 0
{
	int s = 0;

	for (int i = 1; i <= n; i++)
	{
		s = s + i;
	}

	return s;
}

int tinhGiaTri9b(int n) // n > 0
{
	int s = 0;

	for (int i = 1; i <= n; i++)
	{
		s = s + i * i;
	}

	return s;
}

double tinhGiaTri9c(int n) // n > 0
{
	double s = 0;

	for (int i = 1; i <= n; i++)
	{
		s = s + 1.0 / i;
	}

	return s;
}

int tinhGiaiThua(int n) // tinhGiaTri9d
{
	int p = 1;

	for (int i = 2; i <= n; i++)	// i bắt đầu từ 1 cũng được!
	{
		p = p * i;
	}

	return p;
}

double tinhGiaTri9f(int n) // n > 0
{
	double s = 0;	// S(0) = 0

	for (int i = 1; i <= n; i++)
	{
		s = sqrt(2 * i + s);	// S(i) = can(2i + S(i - 1))
	}

	return s;
}
// 9e, 9g -> 9q có thể làm theo 2 cách:
// Cách 1: viết thêm các hàm tính lũy thừa và tính giai thừa rồi gọi sử dụng
//         (cách này viết dài nhưng dễ đúng)
// Cách 2: tính số hạng thứ i dựa vào số hạng thứ i - 1 đã tính trước đó
//         (cách này viết ngắn nhưng dễ sai)
//         (lưu ý đảo dấu hoặc dấu tính riêng)
int tinhGiaTri9e_Cach1(int n) // n > 0
{
	int s = 0;

	for (int i = 1; i <= n; i++)
	{
		s = s + tinhGiaiThua(i);
	}

	return s;
}

int tinhGiaTri9e_Cach2(int n) // n > 0
{
	int s = 0;
	int gti = 1; // i = 0 => 0! = 1

	for (int i = 1; i <= n; i++)
	{
		gti = gti * i;
		s = s + gti;
	}

	return s;
}

double tinhGiaTri9g_Cach2a(int n) // n > 0
{
	double s = 1;
	double gti = 1; // i = 0 => 1/0! = 1

	for (int i = 1; i <= n; i++)
	{
		gti = gti * 1 / i; // Bao gồm tử/mẫu
		s = s + gti;
	}

	return s;
}

double tinhGiaTri9g_Cach2b(int n) // n > 0
{
	double s = 1;
	double gti = 1; // i = 0 => 0! = 1

	for (int i = 1; i <= n; i++)
	{
		gti = gti * i; // Chỉ tính mẫu số
		s = s + 1 / gti;
	}

	return s;
}

double tinhGiaTri9h_Cach2(int n, double x) // n > 0
{
	double s = x;
	double gti = x;	// i = 0

	for (int i = 1; i <= n; i++)
	{
		gti = -gti * (x*x) / ((2*i)*(2*i+1));
		s = s + gti;
	}

	return s;
}

double tinhGiaTri9i_Cach2(int n, double x) // n > 0
{
	double s = 1;
	double gti = 1;	// i = 0

	for (int i = 1; i <= n; i++)
	{
		gti = -gti * (x*x) / ((2*i-1)*(2*i));// Bao gồm tử/mẫu
		s = s + gti;
	}

	return s;
}

double tinhGiaTri9j_Cach2(int n, double x) // n > 0
{
	double s = 1;
	double gti = 1;	// i = 0

	for (int i = 1; i <= n; i++)
	{
		gti = gti * x;
		s = s + gti;
	}

	return s;
}

// tinhGiaTri9k chính là bài tinhGiaTri9i

#define PI 3.14159
double tinhGiaTri9l_Cach2(int n, double x) // n > 0
{
	double s = PI/2 - x;
	double gti = -x; // i = 0

	for (int i = 1; i <= n; i++)
	{
		gti = -gti * (x*x);	// Chỉ tính tử số
		s = s + gti / (2*i+1);
	}

	return s;
}

double tinhGiaTri9m_Cach2(int n, double x) // n > 0
{
	double s = x;
	double gti = x; // i = 1

	for (int i = 2; i <= n; i++)
	{
		gti = -gti * (x*x);	// Chỉ tính tử số
		s = s + gti / (2*i-1);
	}

	return s;
}

double tinhGiaTri9n_Cach2(int n, double x) // n > 0
{
	double s = 1;
	double gti = 1; // i = 0

	for (int i = 1; i <= n; i++)
	{
		gti = gti * x / i; // Bao gồm tử số và mẫu số
		s = s + gti;
	}

	return s;
}

double tinhGiaTri9o_Cach2(int n, double x) // n > 0
{
	double s = x;
	double gti = x; // i = 1

	for (int i = 2; i <= n; i++)
	{
		gti = -gti * x;	// Chỉ tính tử số
		s = s + gti / i;
	}

	return s;
}

double tinhGiaTri9p_Cach2(int n, double x) // n > 0
{
	double s = 2*x;
	double gti = 2*x; // i = 1

	for (int i = 2; i <= n; i++)
	{
		gti = gti * (x*x); // Chỉ tính tử số
		s = s + gti / (2*i-1);
	}

	return s;
}

double tinhGiaTri9q_Cach2(int n, double x) // n > 0
{
	double s = x;
	double gti = x; // i = 0

	for (int i = 1; i <= n; i++)
	{
		gti = -gti * (x*x) / ((2*i)*(2*i+1)); // Bao gồm tử số và mẫu số
		s = s + gti;
	}

	return s;
}

// 2 hàm sau hỗ trợ cho bài 10, 11, 12
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

// Bài 10
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

// Bài 11
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

// Bài 12
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

// Phần này chỉ để chạy thử, khi đi thi không cần làm!
#define _USE_MATH_DEFINES
#include <math.h>
double doiDoSangRadian(double d)
{
	// 360 độ <=> 2PI radian
	//   d độ <=> d * 2PI / 360
	return d * 2 * M_PI / 360;
}

void main()
{
	double d;

	cout << "Nhap x (do): ";
	cin >> d;
	
	double x = doiDoSangRadian(d);
	int n = 15;	// n càng lớn càng chính xác

	// 9i, 9k. Tính cos(d)
	cout << "9i, 9k. Tinh cos(" << d << ")" << endl;
	cout << "=> Cach 1: " << cos(x) << endl;
	cout << "=> Cach 2: " << tinhGiaTri9i_Cach2(n, x) << endl << endl;
	
	// 9q. Tính sin(d)
	cout << "9q. Tinh sin(" << d << ")" << endl;
	cout << "=> Cach 1: " << sin(x) << endl;
	cout << "=> Cach 2: " << tinhGiaTri9q_Cach2(n, x) << endl << endl;

	// 9m. Tính arctan(d)
	cout << "9m. Tinh arctan(" << d << ")" << endl;
	cout << "=> Cach 1: " << atan(x) << endl;
	cout << "=> Cach 2: " << tinhGiaTri9m_Cach2(n, x) << endl;
}