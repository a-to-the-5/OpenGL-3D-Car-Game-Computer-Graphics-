#include <stdio.h>
#include <GL/glut.h>
#include <iostream.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include "texture.h"

using namespace std;
using std::cout;

#define MAX_VERTICES 100000 // Max number of vertices (for each object)
#define MAX_POLYGONS 100000 // Max number of polygons (for each object)
#define BUILD 1
#define GREEN 2
#define BLUE 3
#define WHITE 4
#define FOUR 1
#define TEN 2
#define FIFTEEN 3
#define TWENTY 4
#define TWENTYF 5
float unit=12.5f;
double buildx=25,buildz=25,buildsize=25;

static float spin=0.0f;
static float come=0.0f;
static int move=0;
static bool stop=0;
static float posx=0.0f;
static float posy=0.0f;

static bool build=0;

static double PI = 4.0 * atan(1.0);

static double alpha = 0;
static double turnAngle = 0.04;
static double speed = 0.0;

static double xPos = 0, zPos = 0;
static double xDir = 0, zDir = 0;

static double camx=50.0, camy=0, camz=-70.0;
/**********************************************************
 *
 * TYPES DECLARATION
 *
 *********************************************************/

/*** Our vertex type ***/
class color
{
public:double r,g,b;
};

class CPoint
{
public:int x,y;
};

class Point
{
public:float x,y,z;
};
class Normal
{
public:float x,y,z;
};
class Face
{
public:int a,b,c,d;
		bool t;
};

class Tex
{
public:float u,v;

};

class Mesh
{
public:Point cpoints[4];


};




bool flagf=1;
static color c1;
static int c=0;
static int scale=1;
static bool flag=0;
static bool flagT=0;
static bool flagFace=0;
static int tri=0;
static int faceCount;
static Point  points[20000];
static Normal normals [20000];
static Face faces [20000];
static Tex texs [50000];
typedef struct{
    float x,y,z;//,xn,yn,zn;
}vertex_type;

/*** The polygon (triangle), 3 number that aim 3 vertex ***/
typedef struct{
    int a,b,c,d;//,xn,yn,zn;
}polygon_type;



/*** The object type ***/
typedef struct {
    vertex_type vertex[MAX_VERTICES];
    polygon_type polygon[MAX_POLYGONS];
} obj_type, *obj_type_ptr;

float s2f(const char* str)
{
	float f;
	sscanf(str, "%f", &f);
	return f;
};

int s2i(const char* str)
{
	int i;
	sscanf(str, "%i", &i);
	return i;
};

void readFile()
{


	ifstream instream ("in.obj",ios::in);
	istringstream sstream;
	string x="";
	char c,c2,c3;
	string t1="";
	string t2="";
	string t3="";
	string t4="";
	instream.ignore(INT_MAX,'\n');
	instream.ignore(INT_MAX,'\n');
//	instream >>c ;
//	cout<<c<<" \n";
getline(instream,x);
sstream.str(x);
	char ch;
	const char* tempc;
	const char* tempf;
	int j=1;
	int n=0;
	int t=0;
	int f=0;
	while(!instream.eof())
//	for(int k=0;k<30;k++)

	{
		if(x[0]=='v')
		{
			//cout<<x<<":X\n";
		//	instream >>c2 ;
		//	cout<<c2<<" c2\n";
			if(x[1]=='n')
			{
				x=x.substr(3,(x.length()-1));
				sstream.str(x);
				sstream >>t1;
				sstream >>t2;
				sstream >>t3;
				tempc=(t1.c_str());
				normals[n].x=s2f(tempc);
				tempc=(t2.c_str());
				normals[n].y=s2f(tempc);
				tempc=(t3.c_str());
				normals[n].z=s2f(tempc);
				cout<<"N: "<<normals[n].x<<" "<<normals[n].y<<" "<<normals[n].z<<"\n";
				n++;
				sstream.clear();
			}
			else
			{//instream.unget();
				if(x[1]=='t')
				{
					x=x.substr(2,(x.length()));
					sstream.str(x);
					//cout<<x<<":x\n";

					//sstream >>t1;
					//cout<<t1<<":t1\n";
					sstream >>t1;
					sstream >>t2;

					//	cout<<t1<<":t1,,"<<t2<<":t2,,"<<t3<<":t3"<<"\n";

				//	cout<<x<<":x After Stream\n";

					tempc=(t1.c_str());
					texs[t].u=s2f(tempc);

					tempc=(t2.c_str());
					texs[t].v=s2f(tempc);


					cout<<"T: "<<texs[t].u<<" "<<texs[t].v<<"\n";
					sstream.clear();

					t++;
				}
				else
				{
					x=x.substr(1,(x.length()));
					sstream.str(x);
					//cout<<x<<":x\n";

					//sstream >>t1;
					//cout<<t1<<":t1\n";
					sstream >>t1;
					sstream >>t2;
					sstream >>t3;
					//	cout<<t1<<":t1,,"<<t2<<":t2,,"<<t3<<":t3"<<"\n";

				//	cout<<x<<":x After Stream\n";

					tempc=(t1.c_str());
					points[j].x=s2f(tempc);

					tempc=(t2.c_str());
					points[j].y=s2f(tempc);

					tempc=(t3.c_str());
					points[j].z=s2f(tempc);
					cout<<"P: "<<points[j].x<<" "<<points[j].y<<" "<<points[j].z<<"\n";
					sstream.clear();

					j++;
			//		cout<<"1 "<<t1<<" 2 "<<t2<<" 3 "<<t3<<"\n";
				}

			}
		}
		else
		{
			if(x[0]=='f')//||flagFace==1)
			{
				//cout<<"FACES";
				x=x.substr(2,(x.length()-1));
				sstream.str(x);
				sstream >>t1;
				sstream >>t2;
				sstream >>t3;
				sstream >>t4;

				//cout<<t4<<":t4\n";
				tempf=(t1.c_str());
				faces[f].a=s2i(tempf);

				tempf=(t2.c_str());
				faces[f].b=s2i(tempf);

				tempf=(t3.c_str());
				faces[f].c=s2i(tempf);

				tempf=(t4.c_str());
				faces[f].d=s2i(tempf);
				if(t4!="")
				{
					faces[f].t=0;
					cout<<"\nF: "<<faces[f].a<<" "<<faces[f].b<<" "<<faces[f].c<<" "<<faces[f].d<<"\n";
				}
				else
				{
					faces[f].t=1;
					cout<<"\nF: "<<faces[f].a<<" "<<faces[f].b<<" "<<faces[f].c<<"\n";
					tri++;
				}
				sstream.clear();
				f++;

			}
			else
			{
				//cout<<"Skip line\n";
				//instream.ignore(INT_MAX,'\n');
				//cout<<x<<":X\n";
			}
		}


	//	instream >>c ;
	getline(instream,x);
	sstream.str(x);
	//	cout<<c<<":c end loop "<<!instream.eof()<<"\n";
		t1="";
		t2="";
		t3="";
		t4="";
		flagT=0;
	}

	faceCount=f;
	cout<<"Finished\nV="<<j-1<<"\nF="<<f<<"\nN="<<n<<"\nT="<<t-1<<"\n";
	cout<<"HELP tri:"<<tri<<"\n";
	instream.close();
	//sstream.close();
};
obj_type object;
/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

/*** The width and height of your window, change it as you like  ***/
int screen_width=1024;
int screen_height=800;

/*** Absolute rotation values (0-359 degrees) and rotiation increments for each frame ***/
double rotation_x=0, rotation_x_increment=0.1;
double rotation_y=90.0, rotation_y_increment=-0.9;
double rotation_z=0, rotation_z_increment=0.03;

/*** Flag for rendering as lines or filled polygons ***/
int filling=1; //0=OFF 1=ON

/*** And, finally our first object! ***/
//obj_type vertex=
//{
//	1.0,0.0,0.0
//};
obj_type cube =
{
    {
   1.000000, -1.000000, -1.000000,
 1.000000, -1.000000, -1.000000,
 1.000000 ,-1.000000, 1.000000,
 -1.000000, -1.000000, 1.000000,
 -1.000000, -1.000000, -1.000000,
 1.000000, 1.000000, -1.000000,
 0.999999, 1.000000, 1.000001,
 -1.000000, 1.000000, 1.000000,
 -1.000000, 1.000000, -1.000000,
 0.519411, 1.000000, -0.519411,
 0.519410, 1.000000, 0.519411,
 -0.519411, 1.000000, -0.519411,
 -0.519411, 1.000000, 0.519411,
 0.519411, 3.007775, -0.519411,
 0.519410, 3.007775, 0.519411,
 -0.519411, 3.007775, -0.519411,
 -0.519411, 3.007775, 0.519411,
    },
    {
1,2,3,4,
5,8,7,6,
1,5,6,2,
2,6,7,3,
3,7,8,4,
5,1,4,8

    }
};

//static float  normals[18]=    {
//-0.000000, -1.000000, 0.000000,
//0.000000, 1.000000, -0.000000,
//1.000000, 0.000000, 0.000000,
//-0.000000 ,-0.000000, 1.000000,
//-1.000000, -0.000000, -0.000000,
//0.000000, 0.000000, -1.000000
//
//    };

static int radius=60;
static CPoint Cpoints[240];
static bool newCirc=1;
static bool newLine=1;
void drawCircle(int x, int y)// int r)
{
	int r = radius;
	int Xo=0;
	int Yo;


	while(Xo<=r){ //x,y
	Yo=sqrt((r*r)-(Xo*Xo));
	//	glVertex2i(Xo+x,Yo+y);
		Cpoints[Xo].x=Xo+x;
		Cpoints[Xo].y=ceil(Yo+y);

		Xo++;}

		for(int j=r-1;j>=0;j--) //x,-y
		{
		//	cout << "x:" << points[j].x<< "  y: "<< 2*y-points[j].y << "\n" ;
			//glVertex2i(points[j].x,2*y-points[j].y);
			Cpoints[Xo].x=Cpoints[j].x;
		Cpoints[Xo].y=2*y-Cpoints[j].y;
		Xo++;
		}

		for(int j=1;j<=r;j++)  //-x,-y
		{
			//cout << "x:" << 2*x-points[j].x<< "  y: "<< 2*y-points[j].y << "\n" ;
			//glVertex2i(2*x-points[j].x,2*y-points[j].y);
			Cpoints[Xo].x=2*x-Cpoints[j].x;
		Cpoints[Xo].y=2*y-Cpoints[j].y;
		Xo++;
		}

		for(int j=r-1;j>=0;j--)  //-x,y
		{
//			cout << "x:" << 2*x-points[j].x<< "  y: "<< points[j].y << "\n" ;
//			glVertex2i(2*x-points[j].x,points[j].y);
			Cpoints[Xo].x=2*x-Cpoints[j].x;
			Cpoints[Xo].y=Cpoints[j].y;
			Xo++;
		}
		cout<<Xo<<"ARRAY\n";


}
/**********************************************************
 *
 * SUBROUTINE init()
 *
 * Used to initialize OpenGL and to setup our world
 *
 *********************************************************/
static int id_texture;
static int groundImage;
static int trei;
static int bImg[4];
int build_count=10;

void  init(void)
{
    glClearColor(1, 1, 1, 0.0); // This clear the background color to dark blue
    glShadeModel(GL_SMOOTH); // Type of shading for the polygons

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);


    //  drawCircle(0,0);
   	glEnable(GL_TEXTURE_2D);
   	id_texture=LoadBitmap("x.bmp"); // The Function LoadBitmap() return the current texture ID
   	groundImage=LoadBitmap("g3--.bmp");

//   	for(int i=0;i<=build_count;i++){
//   		char* s;
//   		sprintf(s,"b%d.bmp",i);
//   		bImg[i]=LoadBitmap(s);
//   	}
	   bImg[0]=LoadBitmap("b0.bmp");
       bImg[1]=LoadBitmap("b1.bmp");
       bImg[2]=LoadBitmap("b2.bmp");
       bImg[3]=LoadBitmap("b3.bmp");
       bImg[4]=LoadBitmap("b4.bmp");
   	// Viewport transformation
    //glViewport(0,0,screen_width,screen_height);

    // Projection transformation
   	//  glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations
   	//   glLoadIdentity(); // We initialize the projection matrix as identity
   	//   gluPerspective(90.0f,(GLfloat)screen_width/(GLfloat)screen_height,1.0f,100.0f); // We define the "viewing volume"

    glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)

    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(/*left*/5*-screen_width/screen_height, /*right*/5*screen_width/screen_height,/*bottom*/ -5, /*top*/ 5,/*near*/ -10,/*far*/ 100);
	glMatrixMode(GL_MODELVIEW);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue
//	glLoadIdentity();
//	gluLookAt(/*camX*/50,/*camY*/0,/*camZ*/-70,
//		   	  /*centerX*/0,/*centerY*/ 0,/*centerZ*/ 0,
//	          /*upX*/0,/*upY*/ 1,/*upZ*/ 0);
}



/**********************************************************
 *
 * SUBROUTINE resize(int,int)
 *
 * This routine must be called everytime we resize our window.
 *
 *********************************************************/


double m3dX,m3dY,m3dZ;

void GetOGLPos(int x, int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	m3dX=posX;
	m3dY=posY;
	m3dZ=posZ;

}


ofstream outs ("build",ios::out);

void myMouse(int button, int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON)
	{
		if(state==GLUT_DOWN)
		{
			if(build){
				outs<<buildx-25<<" "<<buildz-25<<" "<<buildsize<<endl;
			}

//			float yellowAmbientDiffuse[] = {1.0f, 0.0f, 0.0f, 1.0f};
//
//        float position[] = {x, 480-y, 18.0f, 1.0f};
//
//        glLightfv(GL_LIGHT1, GL_AMBIENT, yellowAmbientDiffuse);
//        glLightfv(GL_LIGHT1, GL_DIFFUSE, yellowAmbientDiffuse);
//        glLightfv(GL_LIGHT1, GL_POSITION, position);
			build=0;

  //      GetOGLPos(x,y);
//		cout<<"mx:"<<m3dX<<"\nmy:"<<m3dY<<"\nmz:"<<m3dZ<<"\n";
		}
	}
}
int active[2]={-1,-1},oldActive[2]={-1.-1};
void mousePassiveMotion(int x, int y)
{
        GetOGLPos(x,y);
		//cout<<"mx:"<<m3dX<<"\nmy:"<<m3dY<<"\nmz:"<<m3dZ<<"\n";
		if(active[0]!=-1 && oldActive[0]!=-1)
		{
			buildx=active[0];
			buildz=active[1];
		}
		//cout<<"buildx:"<<buildx<<"\nbuildz:"<<buildz<<"\n";
		//buildx=m3dX;
		//buildz=m3dZ;


}

void ourWorld()
{
	float colorBlue[] = { 1.0f, 1.0f, 1.0f,1.0f };
glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorBlue);
float specReflection[] = { 0.8f, 0.8f, 0.8f, 1.0f };
glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);

	// GROUND PLANE
    glBindTexture(GL_TEXTURE_2D,groundImage);
    float ground=-8.0f,length=500.0,width=500.0;
    glBegin(GL_QUADS);
   		glTexCoord2f(0.0f, width/10);
   		glVertex3f(length,ground,width);
		glTexCoord2f(length/10, width/10);
		glVertex3f(-length,ground,width);
		glTexCoord2f(length/10, 0.0f);
		glVertex3f(-length,ground,-width);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(length,ground,-width);
	glEnd();
glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
filling=0;
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	// Ground Mesh
	glLineWidth(4);
	int mCount=0;
	for(float j=-500.0;j<500;j+=unit)
	{
		for(float i=-500.0;i<500;i+=unit)
		{
			double maxmZ=max(j,j+unit);
			double minmZ=min(j,j+unit);
			double maxmX=max(i,i+unit);
			double minmX=min(i,i+unit);
			if(m3dX<maxmX && m3dX>minmX && m3dZ<maxmZ && m3dZ>minmZ )
			{
				oldActive[0]=active[0];
				oldActive[1]=active[1];
				active[0]=i+unit;
				active[1]=j+unit;
				glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
				filling=1;
					glBegin(GL_QUADS);
					//glColor3f(1.0,0.0,0.0);
		   		glVertex3f(i,ground+0.1,j);
		   	//	glTexCoord2f(i, width/10);

			glVertex3f(i,ground+0.1,j+unit);
			//	glTexCoord2f(length/10, width/10);

					glVertex3f(i+unit,ground+0.1,j+unit);
			//	glTexCoord2f(length/10, 0.0f);
				glVertex3f(i+unit,ground+0.1,j);
			//	glTexCoord2f(0.0f, 0.0f);
			glEnd();
			glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
			filling=0;
			}
			else
			{glBegin(GL_QUADS);
		   		glVertex3f(i,ground+0.1,j);
		   		glTexCoord2f(i, width/10);

			glVertex3f(i,ground+0.1,j+unit);
				glTexCoord2f(length/10, width/10);

					glVertex3f(i+unit,ground+0.1,j+unit);
				glTexCoord2f(length/10, 0.0f);
				glVertex3f(i+unit,ground+0.1,j);
				glTexCoord2f(0.0f, 0.0f);
			glEnd();
			}
		}
	}
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	filling=1;
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// BUILDINGS
	ifstream inStream ("build",ios::in);
	float xbase, zbase, xbase2, zbase2;
	float build_height;
	int tile=10;
	for(int j=0;j<build_count;j++)
	{
		glBindTexture(GL_TEXTURE_2D,bImg[j]);
		glBegin(GL_QUADS);
		inStream>>xbase>>zbase>>build_height;
		xbase2=xbase+ 4 *12.5;
		zbase2=zbase+ 4 *12.5;

			glTexCoord2d(0,0);
			glVertex3f(xbase,ground,zbase);
			glTexCoord2f(0,tile);
			glVertex3f(xbase,build_height,zbase);
			glTexCoord2f(tile,tile);
			glVertex3f(xbase,build_height,zbase2);
			glTexCoord2f(tile,0);
			glVertex3f(xbase,ground,zbase2);

			glTexCoord2d(0,0);
			glVertex3f(xbase,ground,zbase2);
			glTexCoord2f(0,tile);
			glVertex3f(xbase,build_height,zbase2);
			glTexCoord2f(tile,tile);
			glVertex3f(xbase2,build_height,zbase2);
			glTexCoord2f(tile,0);
			glVertex3f(xbase2,ground,zbase2);

			glTexCoord2d(0,0);
			glVertex3f(xbase2,ground,zbase2);
			glTexCoord2f(0,tile);
			glVertex3f(xbase2,build_height,zbase2);
			glTexCoord2f(tile,tile);
			glVertex3f(xbase2,build_height,zbase);
			glTexCoord2f(tile,0);
			glVertex3f(xbase2,ground,zbase);

			glTexCoord2d(0,0);
			glVertex3f(xbase2,ground,zbase);
			glTexCoord2f(0,tile);
			glVertex3f(xbase2,build_height,zbase);
			glTexCoord2f(tile,tile);
			glVertex3f(xbase,build_height,zbase);
			glTexCoord2f(tile,0);
			glVertex3f(xbase,ground,zbase);

		glEnd();
		glLineWidth(1);
	}
}

void resize (int width, int height)
{
    screen_width=width; // We obtain the new screen width values and store it
    screen_height=height; // Height value

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We clear both the color and the depth buffer so to draw the next frame
    glViewport(0,0,screen_width,screen_height); // Viewport transformation

    glMatrixMode(GL_PROJECTION); // Projection transformation
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,1.0f,1000.0f);

    glutPostRedisplay (); // This command redraw the scene (it calls the same routine of glutDisplayFunc)
}

void processMenuEvents(int option)
{
	buildsize=(option+2)*20;
	build=1;
	cout<<"SHOWME "<<buildsize<<endl;
}

void createGLUTMenus() {

	int menu,submenu,size;


	// create the menu and
	// tell glut that "processMenuEvents" will
	// handle the events

	size = glutCreateMenu(processMenuEvents);

	glutAddMenuEntry("60", 1 );
	glutAddMenuEntry("80", 2 );
	glutAddMenuEntry("100", 3 );
	glutAddMenuEntry("120", 4 );
	glutAddMenuEntry("140", 5 );
	glutAddMenuEntry("160", 6 );
	glutAddMenuEntry("180", 7 );
	glutAddMenuEntry("200", 8 );
	glutAddMenuEntry("220", 9 );
	glutAddMenuEntry("240", 10 );

	submenu = glutCreateMenu(processMenuEvents);
	glutAddSubMenu("SIZE",size);


	menu = glutCreateMenu(processMenuEvents);

	//add entries to our menu


	glutAddSubMenu("ADD Building",submenu);


	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}



/**********************************************************
 *
 * SUBROUTINE keyboard(unsigned char,int,int)
 *
 * Used to handle the keyboard input (ASCII Characters)
 *
 *********************************************************/
static bool acc=0;
static bool R=0;
static bool L=0;
static double X=0.0;
static double initX=0.0;
static double Y=0.0;
static int incMove=1;
static int cirCount=0;
void keyboard (unsigned char key, int x, int y)
{

//	//cout<<(int)key<<":KEY!!\n";
//	if(key!='d'&&key!='a')
//	{
//		acc=0;
//	}
//
//    switch (key)
//    {
//
//        case ' ':
//            rotation_x_increment=0;
//            rotation_y_increment=0;
//            rotation_z_increment=0;
//        break;
//        case 'r': case 'R':
//            if (filling==0)
//            {
//                glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
//                filling=1;
//            }
//            else
//            {
//                glPolygonMode (GL_FRONT_AND_BACK, GL_LINE); // Polygon rasterization mode (polygon outlined)
//                filling=0;
//            }
//        break;
//        case '+':
//        spin+=10;
//        break;
//        case '-':
//       spin-=10;
//        break;
//        case 'c':
//       come+=5.0f;
//        break;
//        case 'v':
//       X=0;
//       Y=0;
//       posx=0;
//       posy=0;
//       incMove=1;
//       rotation_y=90.0;
//       cirCount=0;
//       newLine=1;
//       newCirc=1;
//
//        break;
//        case 's':
//       camx=camx-1.0;
//   	   cout<<"Camx:"<<camx<<endl;
//   	   glLoadIdentity();
//	gluLookAt(camx,4,camz, 0, 0, 0, 1, 0, 0);
//        break;
//        case 'w':
//     //   stop=0;
//       	camx=camx+1.0;
//      	cout<<"Camx:"<<camx<<endl;
//      	glLoadIdentity();
//	gluLookAt(camx,camy,camz, 0, 0, 0, 1, 0, 0);
//        break;
//        case 'd':
//      	camz=camz+1.0;
//    	cout<<"Camx:"<<camx<<endl;
//    	glLoadIdentity();
//	gluLookAt(camx,camy,camz, 0, 0, 0, 1, 0, 0);
//        break;
//        case 'a':
//      	camz=camz-1.0;
//      	cout<<"Camz:"<<camz<<endl;
//      	glLoadIdentity();
//	gluLookAt(camx,camy,camz, 0, 0, 0, 1, 0, 0);
//      	break;
//
//        case 'z':
//      	camy=camy+1.0;
//      	cout<<"Camy:"<<camy<<endl;
//      	glLoadIdentity();
//	gluLookAt(camx,camy,camz, 0, 0, 0, 1, 0, 0);
//      	break;
//
//      	 case 'x':
//      	camy=camy-1.0;
//      	cout<<"Camy:"<<camy<<endl;
//
//      	glLoadIdentity();
//       	glMatrixMode(GL_PROJECTION);
//	gluPerspective( /* degrees field of view */ 45.0,
//    /* aspect ratio */ 1.0, /* Z near */ camx, /* Z far */ 70.0);
//       glMatrixMode(GL_MODELVIEW);
//	gluLookAt(camx,camy,camz, 0, 0, 0, 1, 0, 0);
//
//      	break;
//
//	    case 'i':
//
//	    speed+=1.0;
//	    break;
//
//	    glLoadIdentity();
//	gluLookAt(camx,4,camz, 0, 0, 0, 1, 0, 0);
//
//    }

if (key=='q')
{
	cout<<"Camx:"<<camx<<"\nCamy:"<<camy<<"\nCamz:"<<camz<<endl;
}

	if (key=='z')
	{

	}

	if (key=='w')
	{
		camy--;
		glutPostRedisplay();
	//	glLoadIdentity();
//	gluLookAt(camx,camy,0, 0, 0, 0, 1, 0, 0);
	}

	if (key=='s')
	{
	camy++;
	glutPostRedisplay();
		//glLoadIdentity();
//	gluLookAt(camx,camy,0, 0, 0, 0, 1, 0, 0);
	}

	if (key=='d')
	{
	camx++;
	glutPostRedisplay();
	//	glLoadIdentity();
//	gluLookAt(camx,camy,0, 0, 0, 0, 1, 0, 0);
	}

	if (key=='a')
	{
		camx--;
		glutPostRedisplay();
	//	glLoadIdentity();
	//gluLookAt(camx,camy,0, 0, 0, 0, 1, 0, 0);
	}
	if (key=='v')
	{

		glLoadIdentity();
//	gluLookAt(0,4,0, 0, 0, 0, 1, 0, 0);
	}
	if (key=='z')
	{
		camz--;
		glutPostRedisplay();
	//	glLoadIdentity();
	//gluLookAt(camx,camy,camz, 0, 0, 0, 1, 0, 0);
	}
	if (key=='x')
	{
		camz++;
		glutPostRedisplay();
	//	glLoadIdentity();
//	gluLookAt(camx,camy,camz, 0, 0, 0, 1, 0, 0);
	}

	 if (key=='r'||key== 'R')
     {
		 if (filling==0)
            {
                glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
                filling=1;
            }
            else
            {
                glPolygonMode (GL_FRONT_AND_BACK, GL_LINE); // Polygon rasterization mode (polygon outlined)
                filling=0;
            }
     }


	if (key==27)
	{
		outs.close();
		exit(0);
	}
    cout<<"Camx:"<<camx<<"\nCamy:"<<camy<<"\nCamz:"<<camz<<endl;

}



/**********************************************************
 *
 * SUBROUTINE keyboard(int,int,int)
 *
 * Used to handle the keyboard input (not ASCII Characters)
 *
 *********************************************************/
 static bool upFlag=0;
static bool downFlag=0;
static bool rightFlag=0;
static bool leftFlag=0;
void controller(int b, int x, int y)
{
	//cout<<b<<endl;
	if(b==100) leftFlag=1;//alpha-=turnAngle;
	else if(b==101) upFlag=1;//speed+=0.1;
	else if(b==102) rightFlag=1;//alpha+=turnAngle;
	else if(b==103) downFlag=1;//speed-=0.05;
	//cout<<"ha?"<< alpha<<endl;

	//cout<<"ha? again"<< alpha<<endl;

//	if(upFlag || downFlag)
//	{
//		if(upFlag)
//		{
//			if(speed<0.2)
//				speed+=0.1;
//		}
//		else
//		{
//			if(downFlag)
//				if(speed>-0.2)
//					speed-=0.05;
//		}
//		if(rightFlag)
//			alpha+=turnAngle;
//		else
//		{
//			if(leftFlag)
//				alpha-=turnAngle;
//		}
//	}

	if(alpha>2*PI)alpha =alpha-2*PI;
	else if(alpha<0) alpha = 2*PI+alpha;
	cout<<"Speed: "<<speed<<"\nAngle:"<<alpha<<endl;
}

void keyboardSpecialUp(int key, int x, int y)
{
	switch((int)key)
	{
     case GLUT_KEY_UP:



     //	speed=0;

      upFlag=0;

      break;

      case GLUT_KEY_DOWN:

    // 	speed=0;

      downFlag=0;
      break;

      case GLUT_KEY_LEFT:


      leftFlag=0;
      break;

      case GLUT_KEY_RIGHT:


      rightFlag=0;
      break;

	}
}








/**********************************************************
 *
 * SUBROUTINE display()
 *
 * This is our main rendering subroutine, called each frame
 *
 *********************************************************/
void newDir()
{
	//cout<<xDir<<" "<<zDir<<" "<<alpha<<endl;
	double nx = sqrt( 1/ ( 1+ pow( tan( alpha ), 2 ) ) );
	zDir = ((alpha>PI/2 && alpha <1.5* PI)? -1:1)*nx*tan( alpha );
	xDir = ((alpha>PI/2 && alpha <1.5* PI)? -1:1)*nx;
	//cout<<xDir<<" "<<zDir<<" "<<alpha<<endl;
}

static int cirCount2=400;
static bool xEnd=0;
static bool yEnd=0;
static double tempX=0;
static double tempY=0;
static bool top=1;

void material_light()
{



		GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
		GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		 GLfloat lightIntensity[]={50.7f,50.7f,51,1.0f};
		// Assign created components to GL_LIGHT0
	    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
	//GLfloat mat_diffuse[]={0.6f,0.6f,0.6,1.0f};
//	GLfloat mat_specular[]={1.0f,1.0f,1.0,1.0f};
	//GLfloat mat_shininess[]={50};

	//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient);
//	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
//	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
//	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
//GLfloat mat_ambient[]={0.2f,0.20f,0.20,1.0f};
//	GLfloat lightIntensity[]={50.7f,50.7f,51,1.0f};
//	//GLfloat light_position[]={0.0f,0.0f,0.0f,0.0f};
////	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
//	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);
//
//		float yellowAmbientDiffuse[] = {1.0f, 0.0f, 0.0f, 1.0f};
//	//     glLightfv(GL_LIGHT1, GL_AMBIENT, yellowAmbientDiffuse);
//     //   glLightfv(GL_LIGHT1, GL_DIFFUSE, yellowAmbientDiffuse);
// //       glLightfv(GL_LIGHT1, GL_POSITION, light_position);
//	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);



}


void  disp(void)//lay(int l)
{
//	if(flagf)
//	{readFile();flagf=0;}
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue
    int l_index;


//     glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	glOrtho(/*left*/5*-64/48, /*right*/5*64/48,/*bottom*/ -5, /*top*/ 5,/*near*/ -10,/*far*/ 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(/*camX*/xPos-55*xDir,/*camY*/400,/*camZ*/zPos-55*zDir,
			   	  /*centerX*/xPos,/*centerY*/ 0,/*centerZ*/ zPos,
		          /*upX*/0,/*upY*/ 1,/*upZ*/ 0);

//	gluLookAt(/*camX*/xPos-55*xDir,/*camY*/15,/*camZ*/zPos-55*zDir,
//		   	  /*centerX*/xPos,/*centerY*/ 0,/*centerZ*/ zPos,
//	          /*upX*/0,/*upY*/ 1,/*upZ*/ 0);
	//gluLookAt(0,0,50 ,0, 0,0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW); // Modeling transformation

    glBindTexture(GL_TEXTURE_2D,id_texture);
    material_light();
    newDir();

    /****************************COLLISION***********************/
	//if(!(xPos+10>100 && zPos<100 && zPos>-10 && speed>0)){
	//	if(!(xPos+10>100 && zPos>130 && zPos<150 && speed>0)){
		xPos+=speed*xDir;
		zPos+=speed*zDir;
	//	}
//	}else
//		speed=0;
	/****************************COLLISION***********************///ATEF

//	if(upFlag)
//	{
//		if(speed<0.9)
//		speed=speed+0.2;
//	}

	if(upFlag || downFlag )
	{
		if(upFlag)
		{
			//if(speed<7)
				speed=2;
		}
		else
		{
			if(downFlag)
				//if(speed>-7)
					speed=-2;
		}
		if(rightFlag)
		{
			if(speed>1)
			alpha+=turnAngle/speed;
			else
			alpha+=turnAngle*speed;
		}
		else
		{
			if(leftFlag)
			{
				if(speed>1)
				alpha-=turnAngle/speed;
				else
				alpha-=turnAngle*speed;
			}
		}
	}
	else
	{
		if(speed>0)
		speed-=0.5;
		else if(speed<0)
		speed+=0.5;

		//if(speed!=0)
		{
			if(rightFlag)
			{
				if(speed>1)
				alpha+=turnAngle;///speed;
				else
				alpha+=turnAngle;//*speed;
			}
			else
			{
				if(leftFlag)
				{
					if(speed>1)
					alpha-=turnAngle;///speed;
					else
					alpha-=turnAngle;//*speed;
				}
			}
		}
	}

	//glPushMatrix();
	//GLfloat position[] =
	//{0.0, 0.0, 12.0, 1.0};
	//glTranslatef(0.0, 0.0, -800.0);
	//glPushMatrix();
	//glRotated(0, 0.0, spin, 0.0);
	//glRotated(0.0, 1.0, 0.0, 0.0);
	//glLightfv(GL_LIGHT0, GL_POSITION, position);
	//GLfloat  position2[] ={-20.0, 0.0, 5.0, 1.0};
	//glLightfv(GL_LIGHT1,GL_POSITION,0);
	//glLightfv(GL_LIGHT1,GL_CONSTANT_ATTENUATION,5.0);
	//glTranslated(0.0, spin, come);
	//glDisable(GL_LIGHTING);
	//glColor3f(0.0, 1.0, 1.0);
	//glutWireCube(5);
	//glEnable(GL_LIGHTING);
	//gluLookAt(camx,camy,camz, 0, 0, 0, 0, 1, 0);
	//glPopMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glPushMatrix();
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	//glLoadIdentity(); // Initialize the model matrix as identity
		glTranslatef(0,0,0.0);
		//glRotatef(180.0,0.0,0.0,1.0);
	//	glTranslated(xPos,come,zPos);
		//glRotated( -alpha*180/PI, 0, 1, 0);
		// Rotations of the object (the model matrix is multiplied by the rotation matrices)
		glRotatef(90.0,0.0,1.0,0.0);

		glutWireCube(20);


		// cout<<"PosX:"<<posx<<"___PosY"<<posy<<"\n";

		double x,y,z;

		int o=0;
		for (l_index=0;l_index<=faceCount;l_index++)
		{
			if(faces[l_index].t==0)
				glBegin(GL_QUADS); // GlBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
			else
				glBegin(GL_TRIANGLES);
			x=c1.r;
			y=c1.g;
			z=c1.b;
			//   glColor3f(x,y,z); // Color for the vertex
			glNormal3f( normals[ l_index ].x,    normals[ l_index].y,    normals[ l_index ].z);
			//NN glNormal3f( normals[faces[l_index].a ].x,    normals[faces[l_index].a].y,    normals[ faces[l_index].a ].z);
			//cout << points[faces[l_index].a].x<<" "<< points[faces[l_index]+1]<<" "<<points[faces[l_index]+2]<<"\n ";

			glTexCoord2f( texs[o].u,texs[ o].v);
			glVertex3f( points[ faces[l_index].a ].x,    points[ faces[l_index].a ].y,    points[ faces[l_index].a ].z);

			o++;

			//NN glNormal3f( normals[ faces[l_index].b ].x,    normals[ faces[l_index].b].y,    normals[ faces[l_index].b].z);
			glTexCoord2f( texs[o].u,texs[o].v);
			glVertex3f( points[ faces[l_index].b ].x,    points[ faces[l_index].b ].y,    points[ faces[l_index].b ].z);
			o++;
			x=c1.b;
			y=c1.r;
			z=c1.g;
			glColor3f(x,y,z);
			//NN glNormal3f( normals[ faces[l_index].c ].x,    normals[ faces[l_index].c ].y,    normals[ faces[l_index].c ].z);
			glTexCoord2f( texs[o].u,texs[o].v);
			glVertex3f( points[ faces[l_index].c ].x,    points[ faces[l_index].c ].y,    points[ faces[l_index].c ].z);
			//glNormal3f(cube.vertex[ cube.polygon[l_index].b ].xn,cube.vertex[ cube.polygon[l_index].b ].yn,cube.vertex[ cube.polygon[l_index].b ].zn);
			o++;
			x=c1.g;
			y=c1.b;
			z=c1.r;

			if(!faces[l_index].t)
			{
				//NN  glNormal3f( normals[ faces[l_index].d ].x,    normals[ faces[l_index].d ].y,    normals[ faces[l_index].d ].z);
				glTexCoord2f( texs[o].u,texs[o].v);
				glVertex3f( points[ faces[l_index].d ].x,    points[ faces[l_index].d ].y,    points[ faces[l_index].d ].z);
				o++;
			}
			if(!flag)
				c ++;

			glEnd();
		}
    glPopMatrix();

    if(!flag)
    {
    	cout<<"Count= "<<c <<"\n";
    	flag=1;
    }

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    ourWorld();

	if(build)
	{
		glPushMatrix();
	glTranslated(buildx,0,buildz);
	glScaled(12.5*4,buildsize,12.5*4);
	glutSolidCube(1);
//	glBegin(GL_QUADS);
//		glVertex3f(-1*unit,5,-1*unit);
//		glVertex3f(-1*unit,5,unit);
//		glVertex3f(unit,5,unit);
//		glVertex3f(unit,5,-1*unit);
//	glEnd();
//

	glPopMatrix();
	}

    glFlush(); // This force the execution of OpenGL commands
    glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer
    //glutTimerFunc(70, disp, 0);

}
//void disp()
//{
//	display(0);
//}


/**********************************************************
 *
 * The main routine
 *
 *********************************************************/

int main(int argc, char **argv)
{
    // We use the GLUT utility to initialize the window, to handle the input and to interact with the windows system
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("import test");

    readFile();
    c1.r=1.0;
    c1.g=0.0;
    c1.b=0.0;
    glutDisplayFunc(disp);
    glutIdleFunc(disp);
    glutReshapeFunc (resize);
    glutKeyboardFunc (keyboard);
    glutSpecialUpFunc (keyboardSpecialUp);
	glutSpecialFunc(controller);
    glutMouseFunc(myMouse);
    glutPassiveMotionFunc(mousePassiveMotion);

	createGLUTMenus();

    init();
    glutMainLoop();

    return(0);
}
