//#define STB_IMAGE_IMPLEMENTATION
//#define GLUT_DISABLE_ATEXIT_HACK
//#include <List>
//#include <vector>
//#include "GLUT.H"
//#include <math.h>
//#include <string.h>
//#include <map>
//#include<iostream>
//#include <fstream>
//#include <sstream>
//#include "My_3DVector.h"
//#include"stb_image.h"
//#include<pthread.h>
//#include<fstream>
//#pragma comment(lib, "pthreadVC2.lib")
//using namespace std;
//#define PI 3.1415
//#define nearplane_width 900//视景体宽度
//#define nearplane_height 900 //视景体高度
//
//
//#define pointLightNum  1
//#define modelNum  100
//#define Weight 0.7
//
//int ModelNum = 0;
//int imageNum = 0;
//
//int nearplane_distance = 1000; //视景体近平面与视点距离
//int farplane_distance = nearplane_distance + 300; //视景体远平面与视点距离
//
//
//
//float eye_x = 0, eye_y = 500, eye_z = 0;	//视觉中心位置
//float look_x = 0, look_y = 0, look_z = 1;		//看向的方向
//float pitch = 0, yaw = PI / 2;		//角度
//int last_x = nearplane_width / 2, last_y = 0;
//
//int speed = 10;		//视觉中心移动速度
//float sensitivity = 0.002;		//鼠标输入灵敏度
//int isperspective = 1;		//是否开启透视投影
//
//class Color {
//public:
//	float data[4];
//	Color(float x = 0, float y = 0, float z = 0, float a = 0) {
//		data[0] = x;
//		data[1] = y;
//		data[2] = z;
//		data[3] = a;
//	}
//};
//
//
//
//class Image {
//public:
//	vector<vector<Color>> data;
//	string imageName;
//	int height;
//	int width;
//}faxian, imageData[modelNum], * image[modelNum] = { NULL };
//
//struct GlobalLight {
//	float r = 1;
//	float g = 1;
//	float b = 1;
//}globalLight;
//
//
//struct PointLight
//{
//	float r = 1;
//	float g = 1;
//	float b = 1;
//
//	bool isOpen = 0;
//
//	float distance = 100;
//	float pitch = 0, yaw = PI / 2;
//	//聚光灯
//	int tag = 0;
//	my_3Dvector Direction;
//	float Cutoff;
//	my_homogeneous_point p;
//	my_homogeneous_point P;
//}pointLight[pointLightNum];
//
//
//struct ModelReflectivity	//物体的反射率
//{
//	float Kar = 0.5, Kag = 0.5, Kab = 0.5;	//全局光反射率
//	float Kdr = 0.3, Kdg = 0.3, Kdb = 0.3;	//漫反射率
//	float Ksr = 0.2, Ksg = 0.2, Ksb = 0.2;	//高光亮系数
//	int n = 100;					//镜反射指数
//	float transparency = 1;
//}mdelReflectivity[modelNum];
//
//struct Edge
//{
//	float cur_X;
//	//当前扫描线与当前边交点的x坐标值
//	float reciprocal_K;
//	//当前边斜率的倒数
//	int max_Y; //当前边两端点最大的y坐标值
//	/*RGB rgb;
//	RGB D_rgb;*/
//	float depth;
//	float D_depth;
//	float dx, dy, dz;	//最低点的法向量
//	float D_dx, D_dy, D_dz;		//法向量变化率
//	float fx, fy;
//	float D_fx, D_fy;
//	Edge(int y, float x, float rec_k, /*RGB temp_RGB, RGB TD_RGB,*/ float z, float D_z, float a, float b, float c, float d, float  e, float f, float g, float h, float i, float j)
//	{
//		max_Y = y;
//		cur_X = x;
//		reciprocal_K = rec_k;
//		/*rgb = temp_RGB;
//		D_rgb = TD_RGB;*/
//		depth = z;
//		D_depth = D_z;
//		dx = a;
//		dy = b;
//		dz = c;
//		D_dx = d;
//		D_dy = e;
//		D_dz = f;
//
//		fx = g;
//		fy = h;
//		D_fx = i;
//		D_fy = j;
//	}
//};
//
////定义面的结构体，包含该面的各个顶点和法向量
//struct my_face_homogeneous
//{
//	vector<my_homogeneous_point> mList;//各个顶点按照逆时针的顺序储存
//	my_3Dvector n; //定义面法向量
//};
//vector<my_face_homogeneous> model[modelNum]; //用来存储三维图形的10个面
//my_homogeneous_point facepoint, a, b, c;//用来存储临时点
//my_3Dvector N1, N2, N3;//用来存储向量以及计算面的法向量
//my_3Dvector v;//用向量v存储视点方向
//my_face_homogeneous tempt; //用于存储面的信息
//vector<my_homogeneous_point> points;
//float	color[nearplane_height][nearplane_width][3];	//像素颜色 0是r 1是g 2是b
//float depth[nearplane_height][nearplane_width];//像素深度
//int Move = 0;
//bool MoveFlag = true;
//
//
//vector<string> split(string T, string P) {
//	vector<string> arr;
//	if (T == "")return arr;
//	unsigned point1 = 0, point2 = 0;
//	if (P == "" || T.find(P, point1) == string::npos) {//不分割或者原字符串找不到分割符
//		arr.push_back(T);
//		return arr;
//	}
//	while ((point1 = T.find(P, point1)) != string::npos) {
//		if (point1 == point2)arr.push_back("");
//		else arr.push_back(T.substr(point2, point1 - point2));
//		point2 = point1 + P.length();//跳过匹配串P
//		point1 += P.length();
//	}
//	if (point2 <= T.length() - 1)arr.push_back(T.substr(point2, T.length() - point2));
//	return arr;
//}
//
//void readImage(Image& image, string a) {
//
//	int n;
//	// 加载图片获取宽、高、颜色通道信息
//	unsigned char* data = stbi_load(a.c_str(), &image.width, &image.height, &n, 0);
//	Color color;
//	vector<Color> heng;
//	int j = 0;
//	for (int i = 0; i < image.width * image.height * n; i++) {
//		color.data[i % n] = (float)data[i] / 255;
//		if (i % n == n - 1) {
//			heng.push_back(color);
//			j++;
//		}
//		if (j == image.width) {
//			j = 0;
//			image.data.push_back(heng);
//			heng.clear();
//		}
//	}
//	stbi_image_free(data);
//
//
//}
//void readMTL(struct ModelReflectivity mdelReflectivity[], string url)
//{
//	ifstream file;
//
//	file.open(url, ios_base::in);
//
//	if (!file.is_open())
//	{
//		cout << "打开文件失败";
//		return;
//	}
//
//	string s;
//	int index = ModelNum;
//	bool first = true;
//	struct ModelReflectivity temp;
//	while (getline(file, s))
//	{
//		if (s[0] == 'n' && s[1] == 'e' && s[2] == 'w' && first)
//		{
//			first = false;
//		}
//		else if (s[0] == 'n' && s[1] == 'e' && s[2] == 'w')
//		{
//			mdelReflectivity[index] = temp;
//			index++;
//			/*cout << mdelReflectivity[index - 1].Kar << " " << mdelReflectivity[index - 1].Ksr << endl;*/
//		}
//		else if (s[0] == 'm' && s[1] == 'a' && s[2] == 'p') {
//			vector<string>str = split(s, " ");
//			int flag = -1;
//			for (int i = 0; i < imageNum; i++) {
//				if (imageData[i].imageName == str[1]) {
//					flag = i;
//					break;
//				}
//			}
//			if (flag != -1) {
//				image[index] = &imageData[flag];
//			}
//			else {
//				readImage(imageData[imageNum], "./海中屋/texture/" + str[1]);
//				imageData[imageNum].imageName = str[1];
//				image[index] = &imageData[imageNum];
//				imageNum++;
//			}
//		}
//		else if (s[0] == 'K' && s[1] == 'a')
//		{
//			vector<string>str = split(s, " ");
//			temp.Kar = atof(str[1].c_str());
//			temp.Kag = atof(str[2].c_str());
//			temp.Kab = atof(str[3].c_str());
//		}
//		else if (s[0] == 'K' && s[1] == 'd')
//		{
//			vector<string>str = split(s, " ");
//			temp.Kdr = atof(str[1].c_str());
//			temp.Kdg = atof(str[2].c_str());
//			temp.Kdb = atof(str[3].c_str());
//		}
//		else if (s[0] == 'K' && s[1] == 's')
//		{
//			vector<string>str = split(s, " ");
//			temp.Ksr = atof(str[1].c_str());
//			temp.Ksg = atof(str[2].c_str());
//			temp.Ksb = atof(str[3].c_str());
//		}
//		else if (s[0] == 'N' && s[1] == 's')
//		{
//			vector<string>str = split(s, " ");
//			temp.n = atof(str[1].c_str());
//		}
//
//	}
//	mdelReflectivity[index] = temp;
//	ModelNum = index + 1;
//
//}
//
//void read(vector<my_face_homogeneous> model[], string url)
//{
//	ifstream file;
//
//	file.open(url, ios_base::in);
//
//	if (!file.is_open())
//	{
//		cout << "打开文件失败";
//		return;
//	}
//
//	string s;
//	vector<my_homogeneous_point> point;
//	my_homogeneous_point curPoint;
//	int j = 0;//点的下标
//	int k = 0;//纹理的下标
//	int f = ModelNum;//模型的下标
//	bool isfirst = 1;
//	vector<my_face_homogeneous> tempModel;
//	while (getline(file, s))
//	{
//
//		if (s[0] == 'v' && s[1] == ' ') {
//
//			vector<string>str = split(s, " ");
//			/*float a;
//			int b;*/
//			curPoint.x = atof(str[1].c_str()) * 20;
//			curPoint.y = atof(str[2].c_str()) * 20;
//			curPoint.z = atof(str[3].c_str()) * 20;
//			/* b= rand() % 101;
//			a = (float)b/ 100;
//			curPoint.rgb.r = a;
//			b = rand() % 101;
//			a = (float)b / 100;
//			curPoint.rgb.g = a;
//			b = rand() % 101;
//			a = (float)b / 100;
//			curPoint.rgb.b = a;*/
//			point.push_back(curPoint);
//		}
//		else if (s[0] == 'v' && s[1] == 'n') {
//			vector<string>str = split(s, " ");
//			point[j].dx = atof(str[1].c_str());
//			point[j].dy = atof(str[2].c_str());
//			point[j].dz = atof(str[3].c_str());
//			j++;
//		}
//		else if (s[0] == 'v' && s[1] == 't') {
//			vector<string>str = split(s, " ");
//			point[k].fx = atof(str[1].c_str());
//			point[k].fy = atof(str[2].c_str());
//			k++;
//		}
//		else if (s[0] == 'u') {
//			if (isfirst == 1)
//				isfirst = 0;
//			else {
//				model[f++] = tempModel;
//				tempModel.clear();
//			}
//
//		}
//
//		else if (s[0] == 'f') {
//			my_face_homogeneous curFace;
//			vector<string>str = split(s, " ");
//			for (int i = 0; i < 3; i++) {
//				vector<string>str1 = split(str[i + 1], "/");
//				curFace.mList.push_back(point[atoi(str1[0].c_str()) - 1]);
//			}
//			if (str.size() == 4)
//			{
//				
//			}
//			N1 = my_3Dvector(curFace.mList[0], curFace.mList[1]);//N1用来存储当前平面上的一个向量
//			N2 = my_3Dvector(curFace.mList[0], curFace.mList[2]);//N2用来存储当前平面上的一个向量
//			N3 = N1.cross_multiply(N2);//N3为当前平面的法向量
//			curFace.n.dx = N3.dx;
//			curFace.n.dy = N3.dy;
//			curFace.n.dz = N3.dz;
//
//			tempModel.push_back(curFace);
//		}
//	}
//	model[f] = tempModel;
//	file.close();
//
//}
//
//struct my_homogeneous_point matrix_multiply_vector(float matrix[][4], struct my_homogeneous_point input_v)
//{
//	struct my_homogeneous_point translated_v;
//	translated_v.x = matrix[0][0] * input_v.x + matrix[0][1] * input_v.y + matrix[0][2] * input_v.z + matrix[0][3] * input_v.ratio;
//	translated_v.y = matrix[1][0] * input_v.x + matrix[1][1] * input_v.y + matrix[1][2] * input_v.z + matrix[1][3] * input_v.ratio;
//	translated_v.z = matrix[2][0] * input_v.x + matrix[2][1] * input_v.y + matrix[2][2] * input_v.z + matrix[2][3] * input_v.ratio;
//	translated_v.ratio = matrix[3][0] * input_v.x + matrix[3][1] * input_v.y + fabsf(matrix[3][2] * input_v.z) + matrix[3][3] * input_v.ratio;
//	return translated_v;
//}
//void translate_model(vector<my_face_homogeneous>& model, int dx, int dy, int dz, float angleY, float angleX)
//{
//	for (int i = 0; i < model.size(); i++)
//	{
//		float pai = 3.14159;
//		float translate_matrix[4][4];
//		memset(translate_matrix, 0, sizeof(int) * 16);
//		translate_matrix[1][1] = 1;
//
//		float angle = angleY;	//先绕y轴
//		/*angle = angle * pai / 180;*/
//		translate_matrix[0][0] = cos(angle);
//		translate_matrix[2][0] = -sin(angle);
//		translate_matrix[0][2] = sin(angle);
//		translate_matrix[2][2] = cos(angle);
//		translate_matrix[3][3] = 1;
//		for (int j = 0; j < model[i].mList.size(); j++)
//		{
//			struct my_homogeneous_point input_v;
//			input_v.x = model[i].mList[j].x;
//			input_v.y = model[i].mList[j].y;
//			input_v.z = model[i].mList[j].z;
//			input_v.ratio = 1;
//			input_v = matrix_multiply_vector(translate_matrix, input_v);
//			model[i].mList[j].x = input_v.x;
//			model[i].mList[j].y = input_v.y;
//			model[i].mList[j].z = input_v.z;
//			model[i].mList[j].ratio = input_v.ratio;
//
//			input_v.x = model[i].mList[j].dx;
//			input_v.y = model[i].mList[j].dy;
//			input_v.z = model[i].mList[j].dz;
//			input_v.ratio = 1;
//			input_v = matrix_multiply_vector(translate_matrix, input_v);
//			model[i].mList[j].dx = input_v.x;
//			model[i].mList[j].dy = input_v.y;
//			model[i].mList[j].dz = input_v.z;
//			model[i].mList[j].ratio = input_v.ratio;
//
//		}
//		memset(translate_matrix, 0, sizeof(int) * 16);
//		translate_matrix[0][0] = 1;
//		angle = angleX;			//再x轴
//		translate_matrix[1][1] = cos(angle);
//		translate_matrix[1][2] = -sin(angle);
//		translate_matrix[2][1] = +sin(angle);
//		translate_matrix[2][2] = cos(angle);
//		translate_matrix[3][3] = 1;
//		for (int j = 0; j < model[i].mList.size(); j++)
//		{
//			struct my_homogeneous_point input_v;
//			input_v.x = model[i].mList[j].x;
//			input_v.y = model[i].mList[j].y;
//			input_v.z = model[i].mList[j].z;
//			input_v.ratio = 1;
//			input_v = matrix_multiply_vector(translate_matrix, input_v);
//			model[i].mList[j].x = input_v.x;
//			model[i].mList[j].y = input_v.y;
//			model[i].mList[j].z = input_v.z;
//			model[i].mList[j].ratio = input_v.ratio;
//
//			input_v.x = model[i].mList[j].dx;
//			input_v.y = model[i].mList[j].dy;
//			input_v.z = model[i].mList[j].dz;
//			input_v.ratio = 1;
//			input_v = matrix_multiply_vector(translate_matrix, input_v);
//			model[i].mList[j].dx = input_v.x;
//			model[i].mList[j].dy = input_v.y;
//			model[i].mList[j].dz = input_v.z;
//			model[i].mList[j].ratio = input_v.ratio;
//
//		}
//		for (int j = 0; j < model[i].mList.size(); j++)
//		{
//			model[i].mList[j].x -= dx;
//			model[i].mList[j].y -= dy;
//			model[i].mList[j].z -= dz;
//		}
//
//	}
//}
//
//void rotate_normal(vector<my_face_homogeneous>& model)
//{
//	for (int i = 0; i < model.size(); i++)
//	{
//		N1 = my_3Dvector(model[i].mList[0], model[i].mList[1]);//N1用来存储当前平面上的一个向量
//		N2 = my_3Dvector(model[i].mList[0], model[i].mList[2]);//N2用来存储当前平面上的一个向量
//		N3 = N1.cross_multiply(N2);//N3为当前平面的法向量
//		model[i].n.dx = N3.dx;
//		model[i].n.dy = N3.dy;
//		model[i].n.dz = N3.dz;
//	}
//
//}
//
//
//
//
//
////初始化三维图形顶点坐标
//void init(void) {
//
//	/*read(model, "./海中屋/海中屋.obj");
//
//	readMTL(mdelReflectivity, "./海中屋/海中屋.mtl");*/
//	/*read(model, "./海中屋/天空盒00a.obj");
//	readMTL(mdelReflectivity, "./海中屋/天空盒00a.mtl");*/
//
//	/*read(model, "./海中屋/apartment.obj");
//
//	readMTL(mdelReflectivity, "./海中屋/apartment.mtl");*/
//	string url = "./海中屋/model/2" + to_string(2);
//			read(model, url + ".obj");
//			readMTL(mdelReflectivity, url + ".mtl");
//	pointLight[0].p.x = 100;
//	pointLight[0].p.y = 100;
//	pointLight[0].p.z = pointLight[0].distance;
//	pointLight[0].tag = 1;
//	pointLight[0].Direction = my_3Dvector(-1, -1, -1);
//	pointLight[0].Cutoff = 100.0f / 360.0f * 3.14f;
//
//	////Red Light
//	//pointLight[1].p.x = pointLight[0].distance;
//	//pointLight[1].p.y = pointLight[0].distance;
//	//pointLight[1].p.z = 0;
//	//pointLight[1].r = 1;
//	//pointLight[1].g = 1;
//	//pointLight[1].b = 0;
//	////Green Light
//	//pointLight[2].p.x = pointLight[0].distance;
//	//pointLight[2].p.y = 0;
//	//pointLight[2].p.z = pointLight[0].distance;
//	//pointLight[2].r = 0;
//	//pointLight[2].g = 1;
//	//pointLight[2].b = 1;
//	////Blue Light
//	//pointLight[3].p.x = -pointLight[0].distance;
//	//pointLight[3].p.y = 0;
//	//pointLight[3].p.z = pointLight[0].distance;
//	//pointLight[3].r = 1;
//	//pointLight[3].g = 0;
//	//pointLight[3].b = 1;
//
//
//
//}
//
//
//
//void translate_plane(vector<my_face_homogeneous>& model)
//{
//	for (int i = 0; i < model.size(); i++)
//	{
//		for (int j = 0; j < model[i].mList.size(); j++)
//		{
//			float x = model[i].mList[j].x + model[i].mList[j].dx;
//			float y = model[i].mList[j].y + model[i].mList[j].dy;
//			float z = model[i].mList[j].z + model[i].mList[j].dz;
//
//
//
//			model[i].mList[j].x -= eye_x;
//			model[i].mList[j].y -= eye_y;
//			model[i].mList[j].z -= eye_z;
//			x -= eye_x;
//			y -= eye_y;
//			z -= eye_z;
//			float pai = 3.14159;
//			float translate_matrix[4][4];
//			struct my_homogeneous_point input_v;
//			memset(translate_matrix, 0, sizeof(int) * 16);
//			translate_matrix[1][1] = 1;
//
//			float angle = atan2(look_z, look_x) + PI / 2;	//先绕y轴
//
//
//			/*angle = angle * pai / 180;*/
//			translate_matrix[0][0] = cos(angle);
//			translate_matrix[2][0] = -sin(angle);
//			translate_matrix[0][2] = sin(angle);
//			translate_matrix[2][2] = cos(angle);
//			translate_matrix[3][3] = 1;
//
//
//			input_v.x = model[i].mList[j].x;
//			input_v.y = model[i].mList[j].y;
//			input_v.z = model[i].mList[j].z;
//			input_v.ratio = 1;
//			input_v = matrix_multiply_vector(translate_matrix, input_v);
//			model[i].mList[j].x = input_v.x;
//			model[i].mList[j].y = input_v.y;
//			model[i].mList[j].z = input_v.z;
//			model[i].mList[j].ratio = input_v.ratio;
//
//			input_v.x = x;
//			input_v.y = y;
//			input_v.z = z;
//			input_v.ratio = 1;
//			input_v = matrix_multiply_vector(translate_matrix, input_v);
//			x = input_v.x;
//			y = input_v.y;
//			z = input_v.z;
//
//			memset(translate_matrix, 0, sizeof(int) * 16);
//			translate_matrix[0][0] = 1;
//
//			angle = atan2(-look_y, sqrtf(look_x * look_x + look_z * look_z));			//再x轴
//			translate_matrix[1][1] = cos(angle);
//			translate_matrix[1][2] = -sin(angle);
//			translate_matrix[2][1] = +sin(angle);
//			translate_matrix[2][2] = cos(angle);
//			translate_matrix[3][3] = 1;
//
//			input_v.x = model[i].mList[j].x;
//			input_v.y = model[i].mList[j].y;
//			input_v.z = model[i].mList[j].z;
//			input_v.ratio = 1;
//			input_v = matrix_multiply_vector(translate_matrix, input_v);
//			model[i].mList[j].x = input_v.x;
//			model[i].mList[j].y = input_v.y;
//			model[i].mList[j].z = input_v.z;
//			model[i].mList[j].ratio = input_v.ratio;
//
//			input_v.x = x;
//			input_v.y = y;
//			input_v.z = z;
//			input_v.ratio = 1;
//			input_v = matrix_multiply_vector(translate_matrix, input_v);
//			x = input_v.x;
//			y = input_v.y;
//			z = input_v.z;
//
//
//
//			model[i].mList[j].z -= nearplane_distance;
//
//			z -= nearplane_distance;
//
//
//			if (isperspective == 1) {
//				memset(translate_matrix, 0, sizeof(int) * 16);
//				translate_matrix[0][0] = 1;
//				translate_matrix[1][1] = 1;
//				translate_matrix[2][2] = 1;
//				translate_matrix[3][3] = 1;
//				translate_matrix[3][2] = 1.0 * 1 / nearplane_distance;;
//
//				struct my_homogeneous_point input_v;
//				input_v.x = model[i].mList[j].x;
//				input_v.y = model[i].mList[j].y;
//				input_v.z = model[i].mList[j].z;
//				input_v.ratio = 1;
//				input_v = matrix_multiply_vector(translate_matrix, input_v);
//				model[i].mList[j].x = input_v.x / input_v.ratio;
//				model[i].mList[j].y = input_v.y / input_v.ratio;
//				model[i].mList[j].z = input_v.z / input_v.ratio;
//				model[i].mList[j].ratio = 1;
//
//				input_v.x = x;
//				input_v.y = y;
//				input_v.z = z;
//				input_v.ratio = 1;
//				input_v = matrix_multiply_vector(translate_matrix, input_v);
//				x = input_v.x / input_v.ratio;
//				y = input_v.y / input_v.ratio;
//				z = input_v.z / input_v.ratio;
//			}
//			model[i].mList[j].dx = x - model[i].mList[j].x;
//			model[i].mList[j].dy = y - model[i].mList[j].y;
//			model[i].mList[j].dz = z - model[i].mList[j].z;
//		}
//	}
//}
//
//void cut(vector<my_face_homogeneous>& model) {
//	for (int i = 0; i < model.size(); i++)
//	{
//		if (model[i].mList.size() == 3 && (model[i].mList[0].x > nearplane_width / 2 && model[i].mList[1].x > nearplane_width / 2 && model[i].mList[2].x > nearplane_width / 2 ||
//			model[i].mList[0].x <-nearplane_width / 2 && model[i].mList[1].x <-nearplane_width / 2 && model[i].mList[2].x <-nearplane_width / 2 ||
//			model[i].mList[0].x > nearplane_height / 2 && model[i].mList[1].x > nearplane_height / 2 && model[i].mList[2].x > nearplane_height / 2 ||
//			model[i].mList[0].x < -nearplane_height / 2 && model[i].mList[1].x < -nearplane_height / 2 && model[i].mList[2].x < -nearplane_height / 2 ||
//			model[i].mList[0].z >0 && model[i].mList[1].z >0 && model[i].mList[2].z >0))
//			model[i].mList.clear();
//	}
//}
//void translate_plane_point(my_homogeneous_point p, my_homogeneous_point& P)
//{
//
//
//	p.x -= eye_x;
//	p.y -= eye_y;
//	p.z -= eye_z;
//
//	float pai = 3.14159;
//	float translate_matrix[4][4];
//	memset(translate_matrix, 0, sizeof(int) * 16);
//	translate_matrix[1][1] = 1;
//
//	float angle = atan2(look_z, look_x) + PI / 2;	//先绕y轴
//
//
//	/*angle = angle * pai / 180;*/
//	translate_matrix[0][0] = cos(angle);
//	translate_matrix[2][0] = -sin(angle);
//	translate_matrix[0][2] = sin(angle);
//	translate_matrix[2][2] = cos(angle);
//	translate_matrix[3][3] = 1;
//	struct my_homogeneous_point input_v;
//	input_v.x = p.x;
//	input_v.y = p.y;
//	input_v.z = p.z;
//	input_v.ratio = 1;
//	input_v = matrix_multiply_vector(translate_matrix, input_v);
//	p.x = input_v.x;
//	p.y = input_v.y;
//	p.z = input_v.z;
//	p.ratio = input_v.ratio;
//
//	memset(translate_matrix, 0, sizeof(int) * 16);
//	translate_matrix[0][0] = 1;
//	angle = atan2(-look_y, sqrtf(look_x * look_x + look_z * look_z));			//再x轴
//	translate_matrix[1][1] = cos(angle);
//	translate_matrix[1][2] = -sin(angle);
//	translate_matrix[2][1] = +sin(angle);
//	translate_matrix[2][2] = cos(angle);
//	translate_matrix[3][3] = 1;
//	input_v.x = p.x;
//	input_v.y = p.y;
//	input_v.z = p.z;
//	input_v.ratio = 1;
//	input_v = matrix_multiply_vector(translate_matrix, input_v);
//	p.x = input_v.x;
//	p.y = input_v.y;
//	p.z = input_v.z;
//	p.ratio = input_v.ratio;
//	p.z -= nearplane_distance;
//	if (isperspective == 1) {
//		memset(translate_matrix, 0, sizeof(int) * 16);
//		translate_matrix[0][0] = 1;
//		translate_matrix[1][1] = 1;
//		translate_matrix[2][2] = 1;
//		translate_matrix[3][3] = 1;
//		translate_matrix[3][2] = 1.0 * 1 / nearplane_distance;;
//
//		input_v.x = p.x;
//		input_v.y = p.y;
//		input_v.z = p.z;
//		input_v.ratio = 1;
//		input_v = matrix_multiply_vector(translate_matrix, input_v);
//		p.x = input_v.x / input_v.ratio;
//		p.y = input_v.y / input_v.ratio;
//		p.z = input_v.z / input_v.ratio;
//
//		p.ratio = 1;
//
//	}
//	P.x = p.x;
//	P.y = p.y;
//	P.z = p.z;
//}
//
//void cal(my_homogeneous_point p1, my_homogeneous_point p2, int num)
//{
//
//	float D = (p2.x - p1.x);
//	my_3Dvector D_dvector((p2.dx - p1.dx) / (p2.x - p1.x), (p2.dy - p1.dy) / (p2.x - p1.x), (p2.dz - p1.dz) / (p2.x - p1.x));
//	my_3Dvector dvector;
//	float D_z = (p2.z - p1.z) / (p2.x - p1.x);
//
//	float D_fx = (p2.fx - p1.fx) / (p2.x - p1.x);
//	float D_fy = (p2.fy - p1.fy) / (p2.x - p1.x);
//
//
//	for (int i = p1.x + 0.5; i <= p2.x + 0.5; i++)
//	{
//		int x = i + nearplane_width / 2, y = p1.y + nearplane_height / 2;
//		if (x < nearplane_width && x >= 0 && y < nearplane_height && y >= 0 && p1.z<0 && p1.z>depth[y][x]) {
//			dvector.dx = p1.dx;
//			dvector.dy = p1.dy;
//			dvector.dz = p1.dz;
//			color[y][x][0] = globalLight.r * mdelReflectivity[num].Kar;
//			color[y][x][1] = globalLight.g * mdelReflectivity[num].Kag;
//			color[y][x][2] = globalLight.b * mdelReflectivity[num].Kab;
//			for (int j = 0; j < pointLightNum; j++) {
//				if (pointLight[j].isOpen == 1) {
//					my_3Dvector L(pointLight[j].P.x - i, pointLight[j].P.y - p1.y, pointLight[j].P.z - p1.z);
//					L.dx /= L.len;
//					L.dy /= L.len;
//					L.dz /= L.len;
//					my_3Dvector V(/*eye_x*/ -i, /*eye_y*/ -p1.y, /*eye_z*/-nearplane_distance - p1.z);
//					V.dx /= V.len;
//					V.dy /= V.len;
//					V.dz /= V.len;
//					float proportion = dvector.dot_multiply(L);
//					my_3Dvector R(2 * proportion * dvector.dx - L.dx, 2 * proportion * dvector.dy - L.dy, 2 * proportion * dvector.dz - L.dz);
//					R.dx /= R.len;
//					R.dy /= R.len;
//					R.dz /= R.len;
//					float theta = dvector.dot_multiply(L);
//					float alpha = R.dot_multiply(V);
//					if (theta < 0) {
//						theta = 0;
//						alpha = 0;
//					}
//					if (alpha <= 0)
//						alpha = 0;
//					else
//						alpha = powf(alpha, mdelReflectivity[num].n);
//					depth[y][x] = p1.z;
//
//					//有法线再加
//					//if (num == 28 || num == 29 || num == 30)
//					//{
//					//	//cout << alpha << " ";
//					//	int index_y_left = int(faxian.height * (p1.fy)) - Move * 50 >= 0 ? int(faxian.height * (p1.fy)) - Move * 50 : 0;
//					//	int index_x_left = int(int(faxian.width * (p1.fx))) - Move * 50 >= 0 ? int(faxian.width * (p1.fx)) - Move * 50 : 0;
//					//	int index_y_right = int(faxian.height * (p1.fy)) + Move * 50 < faxian.height ? int(faxian.height * (p1.fy)) + Move * 50 : faxian.height;
//					//	int index_x_right = int(faxian.width * (p1.fx)) + Move * 50 < faxian.width ? int(faxian.width * (p1.fx)) + Move * 50 : faxian.width;
//					//	//cout << index_y_left<<" " << index_x_left << " " << index_y_right << " " << index_x_right << " " << int(faxian.height * (p1.fy)) << " " << int(faxian.width * (p1.fx)) <<endl;
//					//	float nor_x = (faxian.data[index_y_left][index_x_left].data[0] * 1.0f / 255.0f - 0.5) + 
//					//		(faxian.data[index_y_right][index_x_right].data[0] * 1.0f / 255.0f - 0.5);
//					//	float nor_y = (faxian.data[index_y_left][index_x_left].data[1] * 1.0f / 255.0f - 0.5) +
//					//		(faxian.data[index_y_right][index_x_right].data[1] * 1.0f / 255.0f - 0.5);
//					//	float nor_z = (faxian.data[index_y_left][index_x_left].data[2] * 1.0f / 255.0f - 0.5) +
//					//		(faxian.data[index_y_right][index_x_right].data[2] * 1.0f / 255.0f - 0.5);
//					//	my_3Dvector normal(nor_x,
//					//		nor_y,
//					//		nor_z);
//
//					//	normal.dx = normal.dx / normal.len;
//					//	normal.dy = normal.dy / normal.len;
//					//	normal.dz = normal.dz / normal.len;
//					//	//cout << normal.dx<<" " << normal.dy << " " << normal.dz << endl;
//					//	theta = -normal.dot_multiply(L);
//
//					//	my_3Dvector r(2 * theta * normal.dx - L.dx, 2 * theta * normal.dy - L.dy, 2 * theta * normal.dz - L.dz);
//					//	r.dx /= r.len;
//					//	r.dy /= r.len;
//					//	r.dz /= r.len;
//					//	theta = dvector.dot_multiply(L);
//					//	alpha = abs(r.dot_multiply(V));
//					//	/*if (alpha <= 0)
//					//		alpha = 0;
//					//	else
//					//		alpha = powf(alpha, 2);*/
//					//		//cout << alpha << endl;
//					//}
//
//					switch (pointLight[j].tag)
//					{
//					case 0:
//
//						color[y][x][0] += pointLight[j].r * mdelReflectivity[num].Kdr * theta + pointLight[j].r * mdelReflectivity[num].Ksr * alpha;
//						color[y][x][1] += pointLight[j].g * mdelReflectivity[num].Kdg * theta + pointLight[j].g * mdelReflectivity[num].Ksg * alpha;
//						color[y][x][2] += pointLight[j].b * mdelReflectivity[num].Kdb * theta + pointLight[j].b * mdelReflectivity[num].Ksb * alpha;
//
//						break;
//					case 1:
//						float Cos = -pointLight[j].Direction.dot_multiply(L);
//						//cout << Cos << " " << cos(pointLight[j].Cutoff )<< endl;
//						if (Cos >= cos(pointLight[j].Cutoff))
//						{
//							float rate = (Cos - cos(pointLight[j].Cutoff)) * 1.0f / (1 - cos(pointLight[j].Cutoff) * 1.0f) * 2.0f;
//							color[y][x][0] += (pointLight[j].r * mdelReflectivity[num].Kdr * theta + pointLight[j].r * mdelReflectivity[num].Ksr * alpha) * rate;
//							color[y][x][1] += (pointLight[j].g * mdelReflectivity[num].Kdg * theta + pointLight[j].g * mdelReflectivity[num].Ksg * alpha) * rate;
//							color[y][x][2] += (pointLight[j].b * mdelReflectivity[num].Kdb * theta + pointLight[j].b * mdelReflectivity[num].Ksb * alpha) * rate;
//						}
//						else {
//							color[y][x][0] += 0.01;
//							color[y][x][1] += 0.01;
//							color[y][x][2] += 0.01;
//						}
//						break;
//					}
//
//				}
//			}
//			color[y][x][0] *= (1 - Weight);
//			color[y][x][1] *= (1 - Weight);
//			color[y][x][2] *= (1 - Weight);
//			if (image[num] != NULL) {
//				int h = int(image[num]->height * (p1.fy));
//				/*if (h < 0)
//					h = 0;
//				else if (h > image[num].height)
//					h = image[num].height - 1;*/
//				int w = int(image[num]->width * (p1.fx));
//				/*if (w < 0)
//					w = 0;
//				else if (w > image[num].width)
//					w = image[num].width - 1;*/
//				if (h < image[num]->height && h>0 && w < image[num]->width && w>0) {
//
//					color[y][x][0] += Weight * image[num]->data[h][w].data[0];
//					color[y][x][1] += Weight * image[num]->data[h][w].data[1];
//					color[y][x][2] += Weight * image[num]->data[h][w].data[2];
//				}
//			}
//
//
//
//		}
//		if (D < 0.5)
//			break;
//		p1.z += D_z;
//		p1.dx += D_dvector.dx;
//		p1.dy += D_dvector.dy;
//		p1.dz += D_dvector.dz;
//		p1.fx += D_fx;
//		p1.fy += D_fy;
//		/*color[y][x].r = p1.rgb.r + proportion * r;
//		color[y][x].g = p1.rgb.g + proportion * g;
//		color[y][x].b = p1.rgb.b + proportion * b;*/
//	}
//}
//
//void generate_ET(map<int, std::vector<Edge>>& ET, my_face_homogeneous polygon)
//{
//	for (int eindex = 0; eindex < polygon.mList.size(); eindex++)
//	{
//		my_homogeneous_point startPoint = polygon.mList[eindex];
//		my_homogeneous_point endPoint = (eindex == (polygon.mList.size() - 1)) ? polygon.mList[0] : polygon.mList[eindex + 1];
//		if (int(endPoint.y) == int(startPoint.y))
//			continue; //水平边不加入ET表//生成一条边
//
//		my_homogeneous_point top_point = startPoint.y > endPoint.y ? startPoint : endPoint;
//		my_homogeneous_point bottom_point = startPoint.y < endPoint.y ? startPoint : endPoint;
//		float rec_k = (top_point.x - bottom_point.x) / (top_point.y - bottom_point.y);
//		float D_dx, D_dy, D_dz, D_fx, D_fy;
//		D_dx = (top_point.dx - bottom_point.dx) / (top_point.y - bottom_point.y);
//		D_dy = (top_point.dy - bottom_point.dy) / (top_point.y - bottom_point.y);
//		D_dz = (top_point.dz - bottom_point.dz) / (top_point.y - bottom_point.y);
//
//		D_fx = (top_point.fx - bottom_point.fx) / (top_point.y - bottom_point.y);
//		D_fy = (top_point.fy - bottom_point.fy) / (top_point.y - bottom_point.y);
//		/*RGB  D_RGB;
//		D_RGB.r = (top_point.rgb.r - bottom_point.rgb.r) / (top_point.y - bottom_point.y);
//		D_RGB.g = (top_point.rgb.g - bottom_point.rgb.g) / (top_point.y - bottom_point.y);
//		D_RGB.b = (top_point.rgb.b - bottom_point.rgb.b) / (top_point.y - bottom_point.y);*/
//		float D_z = (top_point.z - bottom_point.z) / (top_point.y - bottom_point.y);
//		Edge one_ET_Edge(top_point.y, bottom_point.x, rec_k, /*bottom_point.rgb, D_RGB,*/ bottom_point.z, D_z, bottom_point.dx, bottom_point.dy, bottom_point.dz, D_dx, D_dy, D_dz, bottom_point.fx, bottom_point.fy, D_fx, D_fy); //以边两端点y坐标最小值为依据对边进行分类和插入排序
//		/*cout << bottom_point.dx << " " << bottom_point.dy << "  " << bottom_point.dz << endl;*/
//		std::map<int, std::vector<Edge>>::iterator it = ET.find(bottom_point.y);
//
//		if (it == ET.end())
//		{
//			std::vector<Edge> new_edge_list;
//			new_edge_list.push_back(one_ET_Edge);
//			ET.insert(std::pair<int, std::vector<Edge>>(bottom_point.y, new_edge_list));
//		}
//		else
//		{
//			bool inserted = false;
//			for (std::vector<Edge>::iterator eit = it->second.begin(); eit != it->second.end(); eit++)
//			{
//				if (bottom_point.x < eit->cur_X || (bottom_point.x == eit->cur_X && rec_k < eit->reciprocal_K))
//				{
//					it->second.insert(eit, one_ET_Edge);
//					inserted = true;
//					break;
//				}
//			}
//			if (false == inserted)
//			{
//				it->second.push_back(one_ET_Edge);
//			}
//		}
//	}
//} /**************************************** 往AET中插入新的Edge集合，并排序* polygon：逆时针排列的顶点数组***************************************/
//void insert_new_edges_into_AET(std::vector<Edge> newedges, vector<Edge>& AET)
//{
//	//根据AET中边的排序规则，对每条边进行插入排序
//	for (std::vector<Edge>::iterator newHead = newedges.begin(); newHead != newedges.end(); newHead++)
//	{
//		bool inserted = false;
//		for (std::vector<Edge>::iterator AET_Head = AET.begin(); AET_Head != AET.end(); AET_Head++)
//		{
//			if (newHead->cur_X < AET_Head->cur_X || (newHead->cur_X == AET_Head->cur_X && newHead->reciprocal_K < AET_Head->reciprocal_K))
//			{
//				AET.insert(AET_Head, *newHead);
//				inserted = true;
//				break;
//			}
//		}
//		if (false == inserted)
//		{
//			AET.push_back(*newHead);
//		}
//	}
//} /**************************************** 扫描线填充***************************************/
//
//void scanline_filling(my_face_homogeneous p, int num)
//{
//	map<int, std::vector<Edge>> ET; //根据y值对所有边进行分类存放
//	vector<Edge> AET;               //活化边表
//	vector<my_homogeneous_point> scan_point; //所有的点
//	AET.clear();
//	glColor3f(0.0f, 0.0f, 1.0f);
//	int ymin = p.mList[0].y, ymax = p.mList[0].y;
//	for (int i = 1; i < p.mList.size(); i++) {
//		if (ymin > p.mList[i].y)
//			ymin = p.mList[i].y;
//		if (ymax < p.mList[i].y)
//			ymax = p.mList[i].y;
//	}
//	generate_ET(ET, p);
//	for (int ypos = ymin; ypos <= ymax; ypos += 1) //逐行遍历所有扫描线
//	{                                                //找到所有两端点y坐标最小值为与当前扫描线ypos相同的所有边
//		std::map<int, std::vector<Edge>>::iterator it = ET.find(ypos);
//		if (it != ET.end())
//		{
//			insert_new_edges_into_AET(it->second, AET); //插入到AET表中
//		}
//		std::vector<int> need_removed_edge_index; //存放需要删除的边序号    //确定填充线段区域并填充
//
//		for (int eindex = 0; eindex < AET.size(); eindex += 2)
//		{
//			my_homogeneous_point point1, point2;
//
//			point1.x = AET[eindex].cur_X;
//			point1.y = ypos;
//
//			point1.dx = AET[eindex].dx;
//			point1.dy = AET[eindex].dy;
//			point1.dz = AET[eindex].dz;
//			point1.z = AET[eindex].depth;
//			point1.fx = AET[eindex].fx;
//			point1.fy = AET[eindex].fy;
//
//
//			AET[eindex].cur_X += 1 * AET[eindex].reciprocal_K;
//			AET[eindex].dx += 1 * AET[eindex].D_dx;
//			AET[eindex].dy += 1 * AET[eindex].D_dy;
//			AET[eindex].dz += 1 * AET[eindex].D_dz;
//			AET[eindex].depth += AET[eindex].D_depth;
//
//			AET[eindex].fx += 1 * AET[eindex].D_fx;
//			AET[eindex].fy += 1 * AET[eindex].D_fy;
//
//
//			//glVertex2f(AET[eindex + 1].cur_X - 1, ypos);
//			point2.x = AET[eindex + 1].cur_X;
//			point2.y = ypos;
//			point2.dx = AET[eindex + 1].dx;
//			point2.dy = AET[eindex + 1].dy;
//			point2.dz = AET[eindex + 1].dz;
//			point2.z = AET[eindex + 1].depth;
//			point2.fx = AET[eindex + 1].fx;
//			point2.fy = AET[eindex + 1].fy;
//
//			AET[eindex + 1].cur_X += 1 * AET[eindex + 1].reciprocal_K;
//
//			AET[eindex + 1].dx += 1 * AET[eindex + 1].D_dx;
//			AET[eindex + 1].dy += 1 * AET[eindex + 1].D_dy;
//			AET[eindex + 1].dz += 1 * AET[eindex + 1].D_dz;
//
//			AET[eindex + 1].depth += AET[eindex + 1].D_depth;
//
//			AET[eindex + 1].fx += 1 * AET[eindex + 1].D_fx;
//			AET[eindex + 1].fy += 1 * AET[eindex + 1].D_fy;
//
//			//放到容器里
//			cal(point1, point2, num);
//			///
//			if (AET[eindex].max_Y == ypos + 1)
//				need_removed_edge_index.push_back(eindex);
//			if (AET[eindex + 1].max_Y == ypos + 1)
//				need_removed_edge_index.push_back(eindex + 1);
//		}
//
//
//		//glEnd();
//		for (int eindex = need_removed_edge_index.size() - 1; eindex >= 0; eindex--)
//		{
//			AET.erase(AET.begin() + need_removed_edge_index[eindex]);
//		}
//	}
//
//}
//
//
//
//void zbuffer(vector<my_face_homogeneous> model, int num) {
//
//	for (int i = 0; i < model.size(); i++) {
//		if (model[i].n.dot_multiply(v) >= 0)
//			model[i].mList.clear();
//	}
//
//
//
//	translate_plane(model);
//	cut(model);
//
//
//	for (int i = 0; i < model.size(); i++) {	//扫描填充
//
//		if (model[i].mList.size() >= 3) {
//			scanline_filling(model[i], num);
//		}
//
//	}
//
//
//}
//
//void* zuffer1(void* arg)
//{
//	for (int i = 0; i < modelNum / 8; i++)
//	{
//		zbuffer(model[i], i);
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//void* zuffer2(void* arg)
//{
//	for (int i = modelNum / 8; i < modelNum / 4; i++)
//	{
//		zbuffer(model[i], i);
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//void* zuffer3(void* arg)
//{
//	for (int i = modelNum / 4; i < modelNum / 8 * 3; i++)
//	{
//		zbuffer(model[i], i);
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//void* zuffer4(void* arg)
//{
//	for (int i = modelNum / 8 * 3; i < modelNum / 2; i++)
//	{
//		zbuffer(model[i], i);
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//void* zuffer5(void* arg)
//{
//	for (int i = modelNum / 2; i < modelNum / 8 * 5; i++)
//	{
//		zbuffer(model[i], i);
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//void* zuffer6(void* arg)
//{
//	for (int i = modelNum / 8 * 5; i < modelNum / 8 * 6; i++)
//	{
//		zbuffer(model[i], i);
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//void* zuffer7(void* arg)
//{
//	for (int i = modelNum / 8 * 6; i < modelNum / 8 * 7; i++)
//	{
//		zbuffer(model[i], i);
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//void* zuffer8(void* arg)
//{
//	for (int i = modelNum / 8 * 7; i < modelNum; i++)
//	{
//		zbuffer(model[i], i);
//	}
//	pthread_exit(NULL);
//	return NULL;
//}
//
//
//
////绘制内容
//void display(void) {
//	for (int i = 0; i < nearplane_height; i++) {
//		for (int j = 0; j < nearplane_width; j++) {
//			depth[i][j] = -99999;
//			color[i][j][0] = 0;
//			color[i][j][1] = 0;
//			color[i][j][2] = 0;
//		}
//	}
//
//
//	v.dx = look_x;		//读取现在的视角方向
//	v.dy = look_y;
//	v.dz = look_z;
//
//	//glClearColor(1.f, 1.f, 1.f, 0.f);
//	//glClear(GL_COLOR_BUFFER_BIT);
//	//draw_coordinate(); //绘制坐标系 
//	for (int i = 0; i < pointLightNum; i++)
//		translate_plane_point(pointLight[i].p, pointLight[i].P);
//	/*for (int i = 0; i < modelNum; i++)
//		zbuffer(model[i], i);*/
//	pthread_t t1, t2, t3, t4, t5, t6, t7, t8;
//	pthread_create(&t1, NULL, zuffer1, NULL);
//	pthread_create(&t2, NULL, zuffer2, NULL);
//	pthread_create(&t3, NULL, zuffer3, NULL);
//	pthread_create(&t4, NULL, zuffer4, NULL);
//	pthread_create(&t5, NULL, zuffer5, NULL);
//	pthread_create(&t6, NULL, zuffer6, NULL);
//	pthread_create(&t7, NULL, zuffer7, NULL);
//	pthread_create(&t8, NULL, zuffer8, NULL);
//	pthread_join(t1, NULL);
//	pthread_join(t2, NULL);
//	pthread_join(t3, NULL);
//	pthread_join(t4, NULL);
//	pthread_join(t5, NULL);
//	pthread_join(t6, NULL);
//	pthread_join(t7, NULL);
//	pthread_join(t8, NULL);
//
//	glBegin(GL_POINTS);
//	for (int i = 0; i < nearplane_height; i++) {
//		for (int j = 0; j < nearplane_width; j++) {
//
//			glColor3f(color[i][j][0], color[i][j][1], color[i][j][2]);
//			glVertex2i(j - nearplane_width / 2, i - nearplane_height / 2);
//		}
//	}
//	glEnd();
//	glutSwapBuffers();
//}
//
////投影方式、modelview方式设置
//void reshape(int w, int h)
//{
//	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	if (w <= h)
//		glOrtho(-0.5 * nearplane_width, 0.5 * nearplane_width, -0.5 * nearplane_height * (GLfloat)nearplane_height / (GLfloat)nearplane_width, 0.5 * nearplane_height * (GLfloat)nearplane_height / (GLfloat)nearplane_width,
//			-nearplane_distance, nearplane_distance + 1000); //相对于视点
//	else
//		glOrtho(-0.5 * nearplane_width, 0.5 * nearplane_width, -0.5 * nearplane_height * (GLfloat)nearplane_width / (GLfloat)nearplane_height, 0.5 * nearplane_height * (GLfloat)nearplane_width / (GLfloat)nearplane_height,
//			-nearplane_distance, nearplane_distance + 1000);
//
//	//if (w <= h)
//	//	glFrustum(-0.5 * nearplane_width, 0.5 * nearplane_width, -0.5 * nearplane_height * (GLfloat)nearplane_height / (GLfloat)nearplane_width, 0.5 * nearplane_height * (GLfloat)nearplane_height / (GLfloat)nearplane_width,
//	//		nearplane_distance, farplane_distance); //相对于视点
//	//else
//	//	glFrustum(-0.5 * nearplane_width, 0.5 * nearplane_width, -0.5 * nearplane_height * (GLfloat)nearplane_width / (GLfloat)nearplane_height, 0.5 * nearplane_height * (GLfloat)nearplane_width / (GLfloat)nearplane_height,
//	//	nearplane_distance, farplane_distance);
//
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	/*gluLookAt(eye_x, eye_y, eye_z, look_x * INT_MAX, look_y * INT_MAX, look_z * INT_MAX, 0, 1, 0);*/
//}
//
////键盘交互事件
//void keyboard(unsigned char key, int x, int y)
//{
//	switch (key)
//	{
//	case 'w':
//	case 'W':
//	{
//		eye_x += cos(yaw) * speed;
//		eye_z += sin(yaw) * speed;
//		break;
//	}
//	case 's':
//	case 'S':
//	{
//		eye_x -= cos(yaw) * speed;
//		eye_z -= sin(yaw) * speed;
//		break;
//	}
//	case 'a':
//	case 'A':
//	{
//		eye_x += sin(yaw) * speed;
//		eye_z -= cos(yaw) * speed;
//		break;
//	}
//	case 'd':
//	case 'D':
//	{
//		eye_x -= sin(yaw) * speed;
//		eye_z += cos(yaw) * speed;
//		break;
//	}
//	case 't':
//	case 'T':
//	{
//		isperspective = 1 - isperspective;
//		break;
//	}
//	case'i':
//	case'I':
//	{
//		pointLight[0].pitch += PI / 10;
//		pointLight[0].p.y = sin(pointLight[0].pitch) * pointLight[0].distance;
//		pointLight[0].p.x = cos(pointLight[0].pitch) * cos(pointLight[0].yaw) * pointLight[0].distance;
//		pointLight[0].p.z = cos(pointLight[0].pitch) * sin(pointLight[0].yaw) * pointLight[0].distance;
//		break;
//	}
//	case'k':
//	case'K':
//	{
//		pointLight[0].pitch -= PI / 10;
//		pointLight[0].p.y = sin(pointLight[0].pitch) * pointLight[0].distance;
//		pointLight[0].p.x = cos(pointLight[0].pitch) * cos(pointLight[0].yaw) * pointLight[0].distance;
//		pointLight[0].p.z = cos(pointLight[0].pitch) * sin(pointLight[0].yaw) * pointLight[0].distance;
//		break;
//	}
//	case'j':
//	case'J':
//	{
//		pointLight[0].yaw += PI / 10;
//		pointLight[0].p.y = sin(pointLight[0].pitch) * pointLight[0].distance;
//		pointLight[0].p.x = cos(pointLight[0].pitch) * cos(pointLight[0].yaw) * pointLight[0].distance;
//		pointLight[0].p.z = cos(pointLight[0].pitch) * sin(pointLight[0].yaw) * pointLight[0].distance;
//		break;
//	}
//	case'l':
//	case'L':
//	{
//		pointLight[0].yaw -= PI / 10;
//		pointLight[0].p.y = sin(pointLight[0].pitch) * pointLight[0].distance;
//		pointLight[0].p.x = cos(pointLight[0].pitch) * cos(pointLight[0].yaw) * pointLight[0].distance;
//		pointLight[0].p.z = cos(pointLight[0].pitch) * sin(pointLight[0].yaw) * pointLight[0].distance;
//		break;
//	}
//	case'1':
//	{
//		pointLight[0].isOpen = 1 - pointLight[0].isOpen;
//		break;
//	}
//	case'2':
//	{
//		pointLight[1].isOpen = 1 - pointLight[1].isOpen;
//		break;
//	}
//	case'3':
//	{
//		pointLight[2].isOpen = 1 - pointLight[2].isOpen;
//		break; }
//	case'4':
//	{
//		pointLight[3].isOpen = 1 - pointLight[3].isOpen;
//		break;
//	}
//	case 'g':
//	case 'G':
//	{
//		if (pitch < PI / 4)
//			pitch += PI / 10;
//		look_y = sin(pitch);
//		look_x = cos(pitch) * cos(yaw);
//		look_z = cos(pitch) * sin(yaw);
//		break;
//	}
//	case 'b':
//	case 'B':
//	{
//		if (pitch > -PI / 4)
//			pitch -= PI / 10;
//		look_y = sin(pitch);
//		look_x = cos(pitch) * cos(yaw);
//		look_z = cos(pitch) * sin(yaw);
//		break;
//	}
//	case 'v':
//	case 'V':
//	{
//		yaw -= PI / 10;
//		look_y = sin(pitch);
//		look_x = cos(pitch) * cos(yaw);
//		look_z = cos(pitch) * sin(yaw);
//		break;
//	}
//	case 'n':
//	case 'N':
//	{
//		yaw += PI / 10;
//		look_y = sin(pitch);
//		look_x = cos(pitch) * cos(yaw);
//		look_z = cos(pitch) * sin(yaw);
//		break;
//	}
//	case 27:
//		exit(0);
//		break;
//	}
//	reshape(nearplane_width, nearplane_height);
//	glutPostRedisplay();
//}
////鼠标交互事件
////void mouse(int x, int y)
////{
////	float offset_x = x - last_x;
////	float offset_y = last_y - y;
////	last_x = x;
////	last_y = y;
////	yaw += offset_x * sensitivity * PI;
////	pitch += offset_y * sensitivity * PI;
////	if (pitch > PI / 4)
////		pitch = PI / 4;
////	else if (pitch < -PI / 4)
////		pitch = -PI / 4;
////	look_y = sin(pitch);
////	look_x = cos(pitch) * cos(yaw);
////	look_z = cos(pitch) * sin(yaw);
////	reshape(nearplane_width, nearplane_height);
////	glutPostRedisplay();
////}
//
////主调函数
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(nearplane_width, nearplane_height);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow("zbuffer");
//	init();
//	glutReshapeFunc(reshape);
//	glutDisplayFunc(display);
//	glutKeyboardFunc(keyboard);
//	/*glutPassiveMotionFunc(mouse);*/
//	glutMainLoop();
//	return 0;
//}