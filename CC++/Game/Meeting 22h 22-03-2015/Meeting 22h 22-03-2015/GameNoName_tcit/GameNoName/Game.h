#pragma once

#define returnedCodeOK		0
#define returnedCodeError	1

// quy định những kí tự được hiển thị ra màn hình
#define mData_blank		' '
#define mData_wall		176
#define mData_player	'x'
#define mData_enemy		'o'
#define mData_gold		'A'


// struct này lưu tọa độ, y là dòng, x là cột
struct coord
{
	int y, x;
};


// bản đồ game, cứ mỗi ô data[i][j] lưu 1 trong 2 trạng thái (đi được hoặc có rừng cây không đi được)
struct sGAMEMAP
{
	unsigned char data[40][40];
	int width, height;
};


//------------------------------------------------------------------------------

struct sPLAYER
{
	coord td; // tọa độ
	int HP;
	int life;

	// trạng thái miễn dịch, nói đúng hơn là miễn dịch trong bao nhiêu nhịp
	// ví dụ quái vật chạm vào player thì player bị hạ HP, life,...và miễn dịch trong 1 giây <=> 10 nhịp game ---> immuneTick = 10
	// immuneTick = 0 tức là hết miễn dịch
	int immuneTick;
	
	coord bullet; // chức năng bắn đạn, comming soon (chắc là comming late hoặc xù luôn)
};


struct sENEMEY
{
	coord td;
};


// mảng các enemy, maximum là 100 con
struct sArrENEMY
{
	sENEMEY data[100];
	int n;
};

//------------------------------------------------------------------------------

// vàng, ăn vàng được là thắng game
struct sGOLD
{
	coord td;
};



// nhập thông tin game
int inputMapData (char FN[], sGAMEMAP &GameMap, sPLAYER &player, sArrENEMY &arrEnemy, sGOLD &gold);


// hiển thị bản đồ, player, quái vật, tình trạng game
void displayGame (const sGAMEMAP &GameMap, const sPLAYER &player, const sArrENEMY &arrEnemy, const sGOLD &gold);


// quái vật di chuyển ngẫu nhiên, có thể xuyên tường
void EnemyMove (sArrENEMY &arrEnemy, int MapWidth, int MapHeight);


// nhập phím từ người chơi và từ đó di chuyển player (trái, phải, lên, xuống)
void controlInputKey (sPLAYER &player, const sGAMEMAP &GameMap);


// điều khiển các sự kiện như quái vật chạm vào player, game over, ăn vàng chiến thắng...
// trả về 1 nếu thắng và trả về -1 nếu thua
int controlEvent (sPLAYER &player, const sArrENEMY &arrEnemy, const sGOLD &gold);