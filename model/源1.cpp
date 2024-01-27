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
//using namespace std;
//#define PI 3.1415
//#define nearplane_width 900//视景体宽度
//#define nearplane_height 900 //视景体高度
//
//
//#define pointLightNum 1
//#define modelNum  200
//#define Weight 0.7
//#define colorDepth 3
//#define maxNum 32766
//
//
//int ModelNum = 0;
//int imageNum = 0;
//
//int nearplane_distance = 1000; //视景体近平面与视点距离
//int farplane_distance = nearplane_distance + 300; //视景体远平面与视点距离
//int shadowDistance = 100;
//
//
//
//float eye_x = 0, eye_y = 1000, eye_z = 0;	//视觉中心位置
//float look_x = 0, look_y = 0, look_z = 1;		//看向的方向
//float pitch = 0, yaw = PI / 2;		//角度
//int last_x = nearplane_width / 2, last_y = 0;
//
//int speed = 10;		//视觉中心移动速度
//float sensitivity = 0.002;		//鼠标输入灵敏度
//int isperspective = 1;		//是否开启透视投影
//
////float Shadow[nearplane_height * 2][nearplane_width * 2][2];  //0对应模型，1对应面	
////float Shadow_Depth[nearplane_height * 2][nearplane_width * 2];//像素深度
//float Shadow[1][1][1];
//float Shadow_Depth[1][1];
//
//vector<int>single_arr = { 1,2,3,8,15,18,19,20,22,23,24,25,26,27,28,29,30,34,35,37,38,40,41,42,43,44,45,47,48,50,52,55,56,61,69,70,71,72,73,74,79,80,81,82,83,84,85,87,88,89,90,91,93
//,93,94,95,96,97,99,100,103 };
//
//my_homogeneous_point light[pointLightNum];
//
//class Color {
//public:
//	float data[4];
//	Color(float x = 0, float y = 0, float z = 0, float a = 1) {
//		data[0] = x;
//		data[1] = y;
//		data[2] = z;
//		data[3] = a;
//	}
//};
//
//
//
//struct Image {
//	vector<vector<Color>> data;
//	string imageName;
//	int height;
//	int width;
//}imageData[modelNum], * image[modelNum] = { NULL };
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
//	bool isOpen = 1;
//
//	float distance = 10000;
//	float pitch = 0, yaw = PI / 2;
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
//	vector<my_homogeneous_point> pointRelativeToLight;
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
//
//	}
//};
//
////定义面的结构体，包含该面的各个顶点和法向量
//struct my_face_homogeneous
//{
//	vector<my_homogeneous_point> mList;//各个顶点按照逆时针的顺序储存
//	my_3Dvector n; //定义面法向量
//	my_homogeneous_point center;
//};
//
//vector<vector<my_face_homogeneous>> Model; //用来存储三维图形的10个面
//my_homogeneous_point facepoint, a, b, c;//用来存储临时点
//my_3Dvector N1, N2, N3;//用来存储向量以及计算面的法向量
////my_3Dvector v;//用向量v存储视点方向
//my_face_homogeneous tempt; //用于存储面的信息
//vector<my_homogeneous_point> points;
//Color color[nearplane_height][nearplane_width][colorDepth];	//像素颜色 0是r 1是g 2是b
//float depth[nearplane_height][nearplane_width][colorDepth];//像素深度
//
////Color color[nearplane_height][nearplane_width][colorDepth];	//像素颜色 0是r 1是g 2是b
////float depth[nearplane_height][nearplane_width][colorDepth];//像素深度
//
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
////const unsigned char* loadfile(const std::string& file, int& size)
////{
////	std::ifstream fs(file.c_str(), std::ios::binary);
////	fs.seekg(0, std::ios::end);
////	size = fs.tellg();
////	char* data = new char[size + 1];
////	fs.seekg(0);
////	fs.read(data, size);
////	fs.close();
////	data[size] = 0;
////	return (unsigned char*)data;
////}
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
//
//			/*cout << mdelReflectivity[index - 1].Kar << " " << mdelReflectivity[index - 1].Ksr << endl;*/
//		}
//		else if (s[0] == 'm' && s[1] == 'a' && s[2] == 'p') {
//			vector<string>str = split(s, " ");
//			int flag = -1;
//
//			for (int i = 0; i < imageNum; i++) {
//				if (imageData[i].imageName == str[1]) {
//					flag = i;
//					break;
//				}
//			}
//
//			if (flag != -1) {
//				image[index] = &imageData[flag];
//			}
//
//			else {
//				readImage(imageData[imageNum], "./海中屋/texture/" + str[1]);
//				/*cout << index << endl;*/
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
//void read(vector<vector<my_face_homogeneous>>& model, string url)
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
//
//
//	vector<vector<float>>v;
//	vector<vector<float>>vn;
//	vector<vector<float>>vt;
//	float c;
//	my_homogeneous_point curPoint;
//
//	bool isfirst = 1;
//	vector<my_face_homogeneous> tempModel;
//	while (getline(file, s))
//	{
//
//		if (s[0] == 'v' && s[1] == ' ') {
//			vector<float> cur;
//
//			vector<string>str = split(s, " ");
//			/*float a;
//			int b;*/
//			c = atof(str[1].c_str()) * 20;
//			cur.push_back(c);
//			c = atof(str[2].c_str()) * 20;
//			cur.push_back(c);
//			c = atof(str[3].c_str()) * 20;
//			cur.push_back(c);
//			/* b= rand() % 101;
//			a = (float)b/ 100;
//			curPoint.rgb.r = a;
//			b = rand() % 101;
//			a = (float)b / 100;
//			curPoint.rgb.g = a;
//			b = rand() % 101;
//			a = (float)b / 100;
//			curPoint.rgb.b = a;*/
//			v.push_back(cur);
//		}
//		else if (s[0] == 'v' && s[1] == 'n') {
//			vector<float> cur;
//			vector<string>str = split(s, " ");
//			c = atof(str[1].c_str());
//			cur.push_back(c);
//			c = atof(str[2].c_str());
//			cur.push_back(c);
//			c = atof(str[3].c_str());
//			cur.push_back(c);
//			vn.push_back(cur);
//		}
//		else if (s[0] == 'v' && s[1] == 't') {
//			vector<float> cur;
//			vector<string>str = split(s, " ");
//			c = atof(str[1].c_str());
//			cur.push_back(c);
//			c = atof(str[2].c_str());
//			cur.push_back(c);
//			vt.push_back(cur);
//		}
//		else if (s[0] == 'u') {
//			if (isfirst == 1)
//				isfirst = 0;
//			else {
//				model.push_back(tempModel);
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
//				my_homogeneous_point p;
//				p.x = v[atoi(str1[0].c_str()) - 1][0];
//				p.y = v[atoi(str1[0].c_str()) - 1][1];
//				p.z = v[atoi(str1[0].c_str()) - 1][2];
//				p.fx = vt[atoi(str1[1].c_str()) - 1][0];
//				p.fy = vt[atoi(str1[1].c_str()) - 1][1];
//				p.dx = vn[atoi(str1[2].c_str()) - 1][0];
//				p.dy = vn[atoi(str1[2].c_str()) - 1][1];
//				p.dz = vn[atoi(str1[2].c_str()) - 1][2];
//				curFace.mList.push_back(p);
//			}
//			curFace.center.x = (curFace.mList[0].x + curFace.mList[1].x + curFace.mList[2].x) / 3;
//			curFace.center.y = (curFace.mList[0].y + curFace.mList[1].y + curFace.mList[2].y) / 3;
//			curFace.center.z = (curFace.mList[0].z + curFace.mList[1].z + curFace.mList[2].z) / 3;
//
//			N1 = my_3Dvector(curFace.mList[0], curFace.mList[1]);//N1用来存储当前平面上的一个向量
//			N2 = my_3Dvector(curFace.mList[0], curFace.mList[2]);//N2用来存储当前平面上的一个向量
//			N3 = N1.cross_multiply(N2);//N3为当前平面的法向量
//			curFace.n.dx = N3.dx;
//			curFace.n.dy = N3.dy;
//			curFace.n.dz = N3.dz;
//			tempModel.push_back(curFace);
//			if (str.size() == 5)
//			{
//				curFace.mList.clear();
//				for (int i = 2; i < 5; i++) {
//					if (i == 4)
//					{
//						i = 0;
//					}
//					vector<string>str1 = split(str[i + 1], "/");
//					my_homogeneous_point p;
//					p.x = v[atoi(str1[0].c_str()) - 1][0];
//					p.y = v[atoi(str1[0].c_str()) - 1][1];
//					p.z = v[atoi(str1[0].c_str()) - 1][2];
//					p.fx = vt[atoi(str1[1].c_str()) - 1][0];
//					p.fy = vt[atoi(str1[1].c_str()) - 1][1];
//					p.dx = vn[atoi(str1[2].c_str()) - 1][0];
//					p.dy = vn[atoi(str1[2].c_str()) - 1][1];
//					p.dz = vn[atoi(str1[2].c_str()) - 1][2];
//					curFace.mList.push_back(p);
//					if (i == 0)
//						break;
//				}
//				curFace.center.x = (curFace.mList[0].x + curFace.mList[1].x + curFace.mList[2].x) / 3;
//				curFace.center.y = (curFace.mList[0].y + curFace.mList[1].y + curFace.mList[2].y) / 3;
//				curFace.center.z = (curFace.mList[0].z + curFace.mList[1].z + curFace.mList[2].z) / 3;
//
//				N1 = my_3Dvector(curFace.mList[0], curFace.mList[1]);//N1用来存储当前平面上的一个向量
//				N2 = my_3Dvector(curFace.mList[0], curFace.mList[2]);//N2用来存储当前平面上的一个向量
//				N3 = N1.cross_multiply(N2);//N3为当前平面的法向量
//				curFace.n.dx = N3.dx;
//				curFace.n.dy = N3.dy;
//				curFace.n.dz = N3.dz;
//				tempModel.push_back(curFace);
//			}
//
//		}
//	}
//	model.push_back(tempModel);
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
//void generate_ET_shadow(map<int, std::vector<Edge>>& ET, my_face_homogeneous polygon)
//{
//	for (int eindex = 0; eindex < polygon.mList.size(); eindex++)
//	{
//		my_homogeneous_point startPoint = polygon.mList[eindex];
//		my_homogeneous_point endPoint = (eindex == (polygon.mList.size() - 1)) ? polygon.mList[0] : polygon.mList[eindex + 1];
//		if (int(endPoint.y) == int(startPoint.y))
//			continue; //水平边不加入ET表//生成一条边
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
//
//
//void translate_Model(vector<my_face_homogeneous>& model, my_homogeneous_point light)
//{
//	for (int i = 0; i < model.size(); i++)
//	{
//		for (int j = 0; j < model[i].mList.size(); j++)
//		{
//			model[i].mList[j].x -= light.x;
//			model[i].mList[j].y -= light.y;
//			model[i].mList[j].z -= light.z;
//		}
//
//
//		float pai = 3.14159;
//		float translate_matrix[4][4];
//		memset(translate_matrix, 0, sizeof(float) * 16);
//		translate_matrix[1][1] = 1;
//		float angle = atan2(light.dz, light.dx) + PI / 2;	//先绕y轴
//
//
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
//
//			input_v = matrix_multiply_vector(translate_matrix, input_v);
//			model[i].mList[j].x = input_v.x;
//			model[i].mList[j].y = input_v.y;
//			model[i].mList[j].z = input_v.z;
//			model[i].mList[j].ratio = input_v.ratio;
//		}
//
//		memset(translate_matrix, 0, sizeof(float) * 16);
//		translate_matrix[0][0] = 1;
//		angle = atan2(-light.dy, sqrtf(light.dx * light.dx + light.dz * light.dz));			//再x轴
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
//
//			input_v = matrix_multiply_vector(translate_matrix, input_v);
//			model[i].mList[j].x = input_v.x;
//			model[i].mList[j].y = input_v.y;
//			model[i].mList[j].z = input_v.z;
//			model[i].mList[j].ratio = input_v.ratio;
//
//
//			model[i].mList[j].z -= shadowDistance;
//
//		}
//		memset(translate_matrix, 0, sizeof(int) * 16);
//		translate_matrix[0][0] = 1;
//		translate_matrix[1][1] = 1;
//		translate_matrix[2][2] = 1;
//		translate_matrix[3][3] = 1;
//		translate_matrix[3][2] = 1.0 * 1 / shadowDistance;
//		for (int j = 0; j < model[i].mList.size(); j++)
//		{
//			struct my_homogeneous_point input_v;
//			input_v.x = model[i].mList[j].x;
//			input_v.y = model[i].mList[j].y;
//			input_v.z = model[i].mList[j].z;
//			input_v.ratio = 1;
//			input_v = matrix_multiply_vector(translate_matrix, input_v);
//			model[i].mList[j].x = input_v.x / input_v.ratio;
//			model[i].mList[j].y = input_v.y / input_v.ratio;
//			model[i].mList[j].z = input_v.z / input_v.ratio;
//
//			model[i].mList[j].ratio = 1;
//		}
//
//
//
//	}
//}
//void translate_point(my_homogeneous_point& p, my_homogeneous_point light)
//{
//	p.x -= light.x;
//	p.y -= light.y;
//	p.z -= light.z;
//
//	float pai = 3.14159;
//	float translate_matrix[4][4];
//	memset(translate_matrix, 0, sizeof(int) * 16);
//	translate_matrix[1][1] = 1;
//
//	float angle = atan2(light.dz, light.dx) + PI / 2;	//先绕y轴
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
//	angle = atan2(-light.dy, sqrtf(light.dx * light.dx + light.dz * light.dz));			//再x轴
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
//
//	p.z -= shadowDistance;
//
//	memset(translate_matrix, 0, sizeof(int) * 16);
//	translate_matrix[0][0] = 1;
//	translate_matrix[1][1] = 1;
//	translate_matrix[2][2] = 1;
//	translate_matrix[3][3] = 1;
//	translate_matrix[3][2] = 1.0 * 1 / shadowDistance;
//
//	input_v.x = p.x;
//	input_v.y = p.y;
//	input_v.z = p.z;
//	input_v.ratio = 1;
//	input_v = matrix_multiply_vector(translate_matrix, input_v);
//	p.x = input_v.x / input_v.ratio;
//	p.y = input_v.y / input_v.ratio;
//	p.z = input_v.z / input_v.ratio;
//
//	p.ratio = 1;
//
//
//
//
//}
//
//void cal_shadow(my_homogeneous_point p1, my_homogeneous_point p2, int model_num, int face_num)
//{
//	float D_z = (p2.z - p1.z) / (p2.x - p1.x);
//	float z = p1.z;
//	for (int i = p1.x; i <= p2.x; i++)
//	{
//		int x = i + nearplane_width * 5, y = p1.y + nearplane_height * 5;
//
//		if (z > Shadow_Depth[y][x] && z < 0) {
//			Shadow_Depth[y][x] = z;
//			//cout<< Shadow_Depth[y][x]<<" ";
//			Shadow[y][x][0] = model_num;
//			Shadow[y][x][1] = face_num;
//
//			//cout << "shadow" << y << " " << x << endl;
//		}
//		z += D_z;
//	}
//}
//void scanline_filling_shadow(my_face_homogeneous p, int model_num, int face_num)
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
//	generate_ET_shadow(ET, p);
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
//
//			AET[eindex].cur_X += 1 * AET[eindex].reciprocal_K;
//			AET[eindex].dx += 1 * AET[eindex].D_dx;
//			AET[eindex].dy += 1 * AET[eindex].D_dy;
//			AET[eindex].dz += 1 * AET[eindex].D_dz;
//			AET[eindex].depth += AET[eindex].D_depth;
//			//glVertex2f(AET[eindex + 1].cur_X - 1, ypos);
//			point2.x = AET[eindex + 1].cur_X;
//			point2.y = ypos;
//			point2.dx = AET[eindex + 1].dx;
//			point2.dy = AET[eindex + 1].dy;
//			point2.dz = AET[eindex + 1].dz;
//			point2.z = AET[eindex + 1].depth;
//
//			AET[eindex + 1].cur_X += 1 * AET[eindex + 1].reciprocal_K;
//			AET[eindex + 1].dx += 1 * AET[eindex + 1].D_dx;
//			AET[eindex + 1].dx += 1 * AET[eindex + 1].D_dy;
//			AET[eindex + 1].dx += 1 * AET[eindex + 1].D_dz;
//			AET[eindex + 1].depth += AET[eindex + 1].D_depth;
//
//			//放到容器里
//			cal_shadow(point1, point2, model_num, face_num);
//			///
//			if (AET[eindex].max_Y == ypos + 1)
//				need_removed_edge_index.push_back(eindex);
//			if (AET[eindex + 1].max_Y == ypos + 1)
//				need_removed_edge_index.push_back(eindex + 1);
//		}
//		//glEnd();
//		for (int eindex = need_removed_edge_index.size() - 1; eindex >= 0; eindex--)
//		{
//			AET.erase(AET.begin() + need_removed_edge_index[eindex]);
//		}
//	}
//}
//void shadowBuffer(my_homogeneous_point light, vector<vector<my_face_homogeneous>> model)
//{
//	//cout << light.x << " " << light.y << endl;
//	for (int i = 0; i < model.size() - 1; i++)	//3：model数
//	{
//		translate_Model(model[i], light);
//
//	}
//	/*cout << model[0][0].mList[0].x << " " << model[0][0].mList[0].y << " " << model[0][0].mList[0].z << endl;*/
//	for (int i = 0; i < model.size() - 1; i++)
//	{
//		for (int j = 0; j < model[i].size(); j++)
//		{
//			if (model[i][j].mList.size() >= 3)
//			{
//
//				scanline_filling_shadow(model[i][j], i, j);
//			}
//		}
//	}
//}
//void creatShadow() {
//	int minX = Model[0][0].mList[0].x;
//	int minY = Model[0][0].mList[0].y;
//	int minZ = Model[0][0].mList[0].z;
//	int maxX = Model[0][0].mList[0].x;
//	int maxY = Model[0][0].mList[0].y;
//	int maxZ = Model[0][0].mList[0].z;
//
//	for (int i = 0; i < Model.size() - 1; i++) {
//		for (int j = 0; j < Model[i].size(); j++) {
//			for (int k = 0; k < Model[i][j].mList.size(); k++)
//			{
//				minX = minX < Model[i][j].mList[k].x ? minX : Model[i][j].mList[k].x;
//				minY = minY < Model[i][j].mList[k].y ? minY : Model[i][j].mList[k].y;
//				minZ = minZ < Model[i][j].mList[k].z ? minZ : Model[i][j].mList[k].z;
//				maxX = maxX > Model[i][j].mList[k].x ? maxX : Model[i][j].mList[k].x;
//				maxY = maxY > Model[i][j].mList[k].y ? maxY : Model[i][j].mList[k].y;
//				maxZ = maxZ > Model[i][j].mList[k].z ? maxZ : Model[i][j].mList[k].z;
//			}
//		}
//	}
//	float centerX = (minX + maxX) / 2.0f;
//	float centerY = (minY + maxY) / 2.0f;
//	float centerZ = (minZ + maxZ) / 2.0f;
//
//	for (int u = 0; u < nearplane_width * 10; u++)
//	{
//		for (int v = 0; v < nearplane_height * 10; v++)
//		{
//			Shadow_Depth[v][u] = -maxNum;
//			Shadow[v][u][0] = -1;
//			Shadow[v][u][1] = -1;
//		}
//	}
//	light[0] = pointLight[0].p;
//	light[0].dx = centerX - light[0].x;		//aaaa
//	light[0].dy = centerY - light[0].y;
//	light[0].dz = centerZ - light[0].z;
//
//	//cout << light.x << " " << light.y << endl;
//	shadowBuffer(light[0], Model);
//	cout << "1" << endl;
//}
////初始化三维图形顶点坐标
//void init(void) {
//	read(Model, "./海中屋/天空盒00a.obj");
//	readMTL(mdelReflectivity, "./海中屋/天空盒00a.mtl");
//
//	for (int i = 0; i < single_arr.size(); i++)
//	{
//		string url = "./海中屋/model/" + to_string(single_arr[i]);
//		//cout << url << endl;
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		cout << ModelNum << " " << Model.size() << " " << i << endl;
//	}
//
//	for (int i = 5; i < 10; i++)
//	{
//		string url = "./海中屋/model/" + to_string(i);
//		//cout << url << endl;
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		cout << ModelNum << " " << Model.size() << " " << i << endl;
//	}
//	for (int i = 1; i < 5; i++)
//	{
//		string url = "./海中屋/model/11_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/12_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/13_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/17_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/32_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/33_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/58_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/78_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/86_" + to_string(i);
//		cout << url << endl;
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		cout << ModelNum << " " << Model.size() << " " << i << endl;
//	}
//	for (int i = 1; i < 6; i++)
//	{
//		string url = "./海中屋/model/4_" + to_string(i);
//		//cout << url << endl;
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/10_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/46_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		cout << ModelNum << " " << Model.size() << " " << i << endl;
//	}
//	for (int i = 1; i < 7; i++)
//	{
//		string url = "./海中屋/model/65_" + to_string(i);
//		//cout << url << endl;
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//
//		url = "./海中屋/model/66_" + to_string(i);
//		//cout << url << endl;
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		cout << ModelNum << " " << Model.size() << " " << i << endl;
//	}
//	for (int i = 1; i < 3; i++)
//	{
//		string url = "./海中屋/model/14_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/21_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/31_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/39_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/53_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/59_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/62_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/63_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/64_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/67_" + to_string(i);
//		//cout << url << endl;
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/68_" + to_string(i);
//		//cout << url << endl;
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/75_" + to_string(i);
//		//cout << url << endl;
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/92_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/98_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/101_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/102_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		cout << ModelNum << " " << Model.size() << " " << i << endl;
//	}
//	for (int i = 1; i < 4; i++)
//	{
//		string url = "./海中屋/model/16_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/57_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/60_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/76_" + to_string(i);
//		//cout << url << endl;
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		url = "./海中屋/model/77_" + to_string(i);
//		//cout << url << endl;
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		cout << ModelNum << " " << Model.size() << " " << i << endl;
//	}
//	for (int i = 1; i < 10; i++)
//	{
//		string url = "./海中屋/model/49_" + to_string(i);
//		read(Model, url + ".obj");
//		readMTL(mdelReflectivity, url + ".mtl");
//		cout << ModelNum << " " << Model.size() << " " << i << endl;
//	}
//	
//	cout << ModelNum << " " << Model.size() << endl;
//
//	/*read(Model, "./海中屋/路地.obj");
//	readMTL(mdelReflectivity, "./海中屋/路地.mtl");*/
//
//
//
//
//
//
//
//	/*for (int i = 30; i < 41; i++) {
//		mdelReflectivity[i].transparency = 0.3;
//	}*/
//
//	pointLight[0].p.x = 0;
//	pointLight[0].p.y = 1000;
//	pointLight[0].p.z = 0;
//
//	/*creatShadow();	*/
//}
//
//void translate_plane(vector<my_face_homogeneous>& model)
//{
//	for (int i = 0; i < model.size(); i++)
//	{
//
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
//
//
//
//
//
//
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
//
//void cal(my_homogeneous_point p1, my_homogeneous_point p2, my_homogeneous_point acp1[], my_homogeneous_point acp2[], int num, int face_num)
//{
//
//	float D = (p2.x - p1.x);
//	my_3Dvector D_dvector((p2.dx - p1.dx) / D, (p2.dy - p1.dy) / D, (p2.dz - p1.dz) / D);
//	my_3Dvector dvector;
//	float D_z = (p2.z - p1.z) / D;
//	float D_fx = (p2.fx - p1.fx) / D;
//	float D_fy = (p2.fy - p1.fy) / D;
//
//	float D_acpx[pointLightNum], D_acpy[pointLightNum], D_acpz[pointLightNum];
//
//	for (int i = 0; i < pointLightNum; i++) {
//		D_acpx[i] = (acp2[i].x - acp1[i].x) / D;
//		D_acpy[i] = (acp2[i].y - acp1[i].y) / D;
//		D_acpz[i] = (acp2[i].z - acp1[i].z) / D;
//	}
//
//	for (int i = p1.x + 0.5; i <= p2.x + 0.5; i++)
//	{
//		int x = i + nearplane_width / 2, y = p1.y + nearplane_height / 2;
//		int k = 0;
//
//		if (x < nearplane_width && x >= 0 && y < nearplane_height && y >= 0 && p1.z < 0) {
//			/*int px = acp1[0].x+ nearplane_width * 5;
//			int py = acp1[0].y + nearplane_height * 5;
//			if (px > 0 && px / 10 < nearplane_height && py > 0 && py / 10 < nearplane_height) {
//				color[py / 10][px / 10][0].data[0] = 1;
//				color[py / 10][px / 10][0].data[1] = 0;
//				color[py / 10][px / 10][0].data[2] = 0;
//			}*/
//
//			bool flag = 0;
//			while (k < colorDepth && p1.z < depth[y][x][k]) {
//				if (color[y][x][k].data[3] == 1 /*||abs(depth[y][x][k]-p1.z)<10*/) {		//碰到不透明物体或者离前面的太近
//					flag = 1;
//					break;
//				}
//				k++;
//			}
//			if (k == colorDepth || flag == 1) {
//				continue;
//			}
//			for (int j = colorDepth - 2; j >= k; j--) {
//				depth[y][x][j + 1] = depth[y][x][j];
//				color[y][x][j + 1].data[0] = color[y][x][j].data[0];
//				color[y][x][j + 1].data[1] = color[y][x][j].data[1];
//				color[y][x][j + 1].data[2] = color[y][x][j].data[2];
//			}
//			dvector.dx = p1.dx;
//			dvector.dy = p1.dy;
//			dvector.dz = p1.dz;
//
//			color[y][x][k].data[0] = globalLight.r * mdelReflectivity[num].Kar;
//			color[y][x][k].data[1] = globalLight.g * mdelReflectivity[num].Kag;
//			color[y][x][k].data[2] = globalLight.b * mdelReflectivity[num].Kab;
//			for (int j = 0; j < pointLightNum; j++) {
//				if (pointLight[j].isOpen == 1) {
//					/*int px = acp1[j].x + nearplane_width * 5;
//					int py = acp1[j].y + nearplane_height * 5;*/
//					/*if(Shadow[py][px][0]!=-1)
//						cout << num << " " << face_num << " " << Shadow[py][px][0] << " " << Shadow[py][px][1] << endl;*/
//					if (/*Shadow[py][px][0] == -1||Shadow[py][px][0] == num && Shadow[py][px][1] == face_num*/1) {
//
//						my_3Dvector L(pointLight[j].P.x - i, pointLight[j].P.y - p1.y, pointLight[j].P.z - p1.z);
//						L.dx /= L.len;
//						L.dy /= L.len;
//						L.dz /= L.len;
//						my_3Dvector V(/*eye_x*/ -i, /*eye_y*/ -p1.y, /*eye_z*/-nearplane_distance - p1.z);
//						V.dx /= V.len;
//						V.dy /= V.len;
//						V.dz /= V.len;
//						float proportion = dvector.dot_multiply(L);
//						my_3Dvector R(2 * proportion * dvector.dx - L.dx, 2 * proportion * dvector.dy - L.dy, 2 * proportion * dvector.dz - L.dz);
//						R.dx /= R.len;
//						R.dy /= R.len;
//						R.dz /= R.len;
//						float theta = dvector.dot_multiply(L);
//						float alpha = R.dot_multiply(V);
//						if (theta < 0) {
//							theta = 0;
//							alpha = 0;
//						}
//						if (alpha <= 0)
//							alpha = 0;
//						else
//							alpha = powf(alpha, mdelReflectivity[num].n);
//						depth[y][x][k] = p1.z;
//
//						color[y][x][k].data[0] += pointLight[j].r * mdelReflectivity[num].Kdr * theta + pointLight[j].r * mdelReflectivity[num].Ksr * alpha;
//						color[y][x][k].data[1] += pointLight[j].g * mdelReflectivity[num].Kdg * theta + pointLight[j].g * mdelReflectivity[num].Ksg * alpha;
//						color[y][x][k].data[2] += pointLight[j].b * mdelReflectivity[num].Kdb * theta + pointLight[j].b * mdelReflectivity[num].Ksb * alpha;
//					}
//				}
//			}
//			color[y][x][k].data[0] *= (1 - Weight);
//			color[y][x][k].data[1] *= (1 - Weight);
//			color[y][x][k].data[2] *= (1 - Weight);
//
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
//					color[y][x][k].data[0] += Weight * image[num]->data[h][w].data[0];
//					color[y][x][k].data[1] += Weight * image[num]->data[h][w].data[1];
//					color[y][x][k].data[2] += Weight * image[num]->data[h][w].data[2];
//					/*cout << color[y][x][k].data[0] << " " << color[y][x][k].data[1] << " " << color[y][x][k].data[2] << endl;*/
//
//					color[y][x][k].data[3] = mdelReflectivity[num].transparency;
//
//				}
//			}
//
//
//
//		}
//		if (D < 0.5)
//			break;
//
//		p1.z += D_z;
//		p1.dx += D_dvector.dx;
//		p1.dy += D_dvector.dy;
//		p1.dz += D_dvector.dz;
//		p1.fx += D_fx;
//		p1.fy += D_fy;
//
//		for (int i = 0; i < pointLightNum; i++) {
//			acp1[i].x += D_acpx[i];
//			acp1[i].y += D_acpy[i];
//			acp1[i].z += D_acpz[i];
//
//		}
//		/*color[y][x].r = p1.rgb.r + proportion * r;
//		color[y][x].g = p1.rgb.g + proportion * g;
//		color[y][x].b = p1.rgb.b + proportion * b;*/
//	}
//}
//void generate_ET(map<int, std::vector<Edge>>& ET, my_face_homogeneous polygon, int model_num, int face_num)
//{
//
//	for (int eindex = 0; eindex < polygon.mList.size(); eindex++)
//	{
//		vector<my_homogeneous_point> pointRelativeToLight;
//		my_homogeneous_point startPoint = polygon.mList[eindex];
//		my_homogeneous_point endPoint = (eindex == (polygon.mList.size() - 1)) ? polygon.mList[0] : polygon.mList[eindex + 1];
//		if (int(endPoint.y) == int(startPoint.y))
//			continue; //水平边不加入ET表//生成一条边
//		my_homogeneous_point acp[2];
//		my_homogeneous_point top_point, bottom_point;
//		if (startPoint.y > endPoint.y) {
//			top_point = startPoint;
//			bottom_point = endPoint;
//			acp[0] = Model[model_num][face_num].mList[eindex];
//			acp[1] = (eindex == (polygon.mList.size() - 1)) ? Model[model_num][face_num].mList[0] : Model[model_num][face_num].mList[eindex + 1];
//		}
//		else {
//			top_point = endPoint;
//			bottom_point = startPoint;
//			acp[0] = (eindex == (polygon.mList.size() - 1)) ? Model[model_num][face_num].mList[0] : Model[model_num][face_num].mList[eindex + 1];
//			acp[1] = Model[model_num][face_num].mList[eindex];
//		}
//		for (int i = 0; i < pointLightNum; i++) {
//			my_homogeneous_point cur0 = acp[0], cur1 = acp[1];
//			translate_point(cur0, light[i]);
//			translate_point(cur1, light[i]);
//			cur1.dx = (cur0.x - cur1.x) / (top_point.y - bottom_point.y);
//			cur1.dy = (cur0.y - cur1.y) / (top_point.y - bottom_point.y);
//			cur1.dz = (cur0.z - cur1.z) / (top_point.y - bottom_point.y);
//			pointRelativeToLight.push_back(cur1);
//
//		}
//
//		/*my_homogeneous_point top_point = startPoint.y > endPoint.y ? startPoint : endPoint;
//		my_homogeneous_point bottom_point = startPoint.y < endPoint.y ? startPoint : endPoint;*/
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
//		Edge one_ET_Edge(top_point.y, bottom_point.x, rec_k, /*bottom_point.rgb, D_RGB,*/ bottom_point.z, D_z, bottom_point.dx, bottom_point.dy, bottom_point.dz, D_dx, D_dy, D_dz, bottom_point.fx,
//			bottom_point.fy, D_fx, D_fy); //以边两端点y坐标最小值为依据对边进行分类和插入排序
//		one_ET_Edge.pointRelativeToLight = pointRelativeToLight;
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
//void scanline_filling(my_face_homogeneous p, int model_num, int face_num)
//{
//	map<int, std::vector<Edge>> ET; //根据y值对所有边进行分类存放
//	vector<Edge> AET;               //活化边表
//	vector<my_homogeneous_point> scan_point; //所有的点
//	AET.clear();
//	/*glColor3f(0.0f, 0.0f, 1.0f);*/
//	int ymin = p.mList[0].y, ymax = p.mList[0].y;
//	for (int i = 1; i < p.mList.size(); i++) {
//		if (ymin > p.mList[i].y)
//			ymin = p.mList[i].y;
//		if (ymax < p.mList[i].y)
//			ymax = p.mList[i].y;
//	}
//	generate_ET(ET, p, model_num, face_num);
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
//			my_homogeneous_point acpoint1[pointLightNum], acpoint2[pointLightNum];
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
//			for (int i = 0; i < pointLightNum; i++) {
//				acpoint1[i].x = AET[eindex].pointRelativeToLight[i].x;
//				acpoint1[i].y = AET[eindex].pointRelativeToLight[i].y;
//				acpoint1[i].z = AET[eindex].pointRelativeToLight[i].z;
//				AET[eindex].pointRelativeToLight[i].x += AET[eindex].pointRelativeToLight[i].dx;
//				AET[eindex].pointRelativeToLight[i].y += AET[eindex].pointRelativeToLight[i].dy;
//				AET[eindex].pointRelativeToLight[i].z += AET[eindex].pointRelativeToLight[i].dz;
//			}
//
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
//			for (int i = 0; i < pointLightNum; i++) {
//				acpoint2[i].x = AET[eindex + 1].pointRelativeToLight[i].x;
//				acpoint2[i].y = AET[eindex + 1].pointRelativeToLight[i].y;
//				acpoint2[i].z = AET[eindex + 1].pointRelativeToLight[i].z;
//				AET[eindex + 1].pointRelativeToLight[i].x += AET[eindex + 1].pointRelativeToLight[i].dx;
//				AET[eindex + 1].pointRelativeToLight[i].y += AET[eindex + 1].pointRelativeToLight[i].dy;
//				AET[eindex + 1].pointRelativeToLight[i].z += AET[eindex + 1].pointRelativeToLight[i].dz;
//			}
//			/*cout << AET[eindex + 1].pointRelativeToLight[0].x << " " << AET[eindex].pointRelativeToLight[0].x << endl;*/
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
//
//			//放到容器里
//			cal(point1, point2, acpoint1, acpoint2, model_num, face_num);
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
//void zbuffer(vector<my_face_homogeneous> model, int model_num) {
//
//
//	/*translate_plane_dvector(model);*/
//	for (int i = 0; i < model.size(); i++) {
//		my_3Dvector v(model[i].center.x - eye_x, model[i].center.y - eye_y, model[i].center.z - eye_z);
//		if (model[i].n.dot_multiply(v) >= 0) {
//			model[i].mList.clear();
//		}
//
//	}
//	translate_plane(model);
//	cut(model);
//	for (int i = 0; i < model.size(); i++) {	//扫描填充
//
//		if (model[i].mList.size() >= 3) {
//			scanline_filling(model[i], model_num, i);
//		}
//
//	}
//
//
//}
////绘制坐标系
//void draw_coordinate()
//{
//	glBegin(GL_LINES);
//	glColor3f(1.0, 0.0, 0.0); //红色x轴
//	glVertex3f(nearplane_width, 0.0, 0.0);
//	glVertex3f(-nearplane_width, 0.0, 0.0);
//	glColor3f(0.0, 1.0, 0.0);//绿色y轴
//	glVertex3f(0.0, nearplane_height, 0.0);
//	glVertex3f(0.0, -nearplane_height, 0.0);
//	glColor3f(0.0, 0.0, 1.0);//蓝色z轴
//	glVertex3f(0.0, 0.0, nearplane_height);
//	glVertex3f(0.0, 0.0, -nearplane_height);
//	glEnd();
//}
////绘制内容
//void display(void) {
//	for (int i = 0; i < nearplane_height; i++) {
//		for (int j = 0; j < nearplane_width; j++) {
//			for (int k = 0; k < colorDepth; k++) {
//				depth[i][j][k] = -99999;
//				color[i][j][k].data[0] = 0;
//				color[i][j][k].data[1] = 0;
//				color[i][j][k].data[2] = 0;
//				color[i][j][k].data[3] = 1;
//			}
//		}
//	}
//
//
//	//v.dx = look_x;		//读取现在的视角方向
//	//v.dy = look_y;
//	//v.dz = look_z;
//
//	//glClearColor(1.f, 1.f, 1.f, 0.f);
//	//glClear(GL_COLOR_BUFFER_BIT);
//	//draw_coordinate(); //绘制坐标系 
//	for (int i = 0; i < pointLightNum; i++)
//		translate_plane_point(pointLight[i].p, pointLight[i].P);
//	for (int i = 0; i < Model.size(); i++)
//		zbuffer(Model[i], i);
//
//	glBegin(GL_POINTS);
//	for (int i = 0; i < nearplane_height; i++) {
//		for (int j = 0; j < nearplane_width; j++) {
//			float weight = 1;
//			Color totalColor;
//			for (int k = 0; k < colorDepth; k++) {
//
//				totalColor.data[0] += color[i][j][k].data[0] * weight * color[i][j][k].data[3];
//				totalColor.data[1] += color[i][j][k].data[1] * weight * color[i][j][k].data[3];
//				totalColor.data[2] += color[i][j][k].data[2] * weight * color[i][j][k].data[3];
//
//				weight -= color[i][j][k].data[3];
//
//				if (weight <= 0)
//					break;
//			}
//
//			glColor3f(totalColor.data[0], totalColor.data[1], totalColor.data[2]);
//			glVertex2i(j - nearplane_width / 2, i - nearplane_height / 2);
//		}
//	}
//
//	/*for (int i = 0; i < 10* nearplane_height; i++) {
//		for (int j = 0; j < 10* nearplane_width; j++) {
//			if (Shadow[i][j][0] != -1) {
//				glColor3f(1, 0, 0);
//				glVertex2i(j/10 - nearplane_width / 2, i/10 - nearplane_height / 2);
//
//			}
//
//
//		}
//	}*/
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
//		creatShadow();
//		break;
//	}
//	case'k':
//	case'K':
//	{
//		pointLight[0].pitch -= PI / 10;
//		pointLight[0].p.y = sin(pointLight[0].pitch) * pointLight[0].distance;
//		pointLight[0].p.x = cos(pointLight[0].pitch) * cos(pointLight[0].yaw) * pointLight[0].distance;
//		pointLight[0].p.z = cos(pointLight[0].pitch) * sin(pointLight[0].yaw) * pointLight[0].distance;
//		creatShadow();
//		break;
//	}
//	case'j':
//	case'J':
//	{
//		pointLight[0].yaw += PI / 10;
//		pointLight[0].p.y = sin(pointLight[0].pitch) * pointLight[0].distance;
//		pointLight[0].p.x = cos(pointLight[0].pitch) * cos(pointLight[0].yaw) * pointLight[0].distance;
//		pointLight[0].p.z = cos(pointLight[0].pitch) * sin(pointLight[0].yaw) * pointLight[0].distance;
//		creatShadow();
//		break;
//	}
//	case'l':
//	case'L':
//	{
//		pointLight[0].yaw -= PI / 10;
//		pointLight[0].p.y = sin(pointLight[0].pitch) * pointLight[0].distance;
//		pointLight[0].p.x = cos(pointLight[0].pitch) * cos(pointLight[0].yaw) * pointLight[0].distance;
//		pointLight[0].p.z = cos(pointLight[0].pitch) * sin(pointLight[0].yaw) * pointLight[0].distance;
//		creatShadow();
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