#include "alien.h"
using namespace std;

void cone(char *r,char *h,char *s,char *stack,char *file)
{
  float radius = strtof(r,0);
  float height = strtof(h,0);
  float A = (2*M_PI)/strtof(s,0);
  float B = (M_PI)/strtof(stack,0);

  float slices = strtof(s,0);
  float stacks = strtof(stack,0);

  float a,b = 0;

  ofstream myfile;
  float x = slices*stacks*8;
  myfile.open(file);
  myfile << x << "\n";

  for (int i = 1; i <= stacks; i++)
  {
    a = 0;
    for(int j = 0;j < slices;j++)
    {
      //bot
      myfile << radius*cos(A*(i-1)) << " " << -height/2 << " " << radius*sin(A*(i-1)) << "\n";
      myfile << radius*cos(A*i) << " " << -height/2 << " " << radius*sin(A*i) << "\n";
      myfile << 0.0f << " " << -height/2 << " " << 0.0f << "\n";
      //top
      myfile << radius*cos(A*i) << " " << -height/2 << " " << radius*sin(A*i) << "\n";
      myfile << radius*cos(A*(i-1)) << " " << -height/2 << " " << radius*sin(A*(i-1)) << "\n";
      myfile << 0.0f << " " << height/2 << " " << 0.0f << "\n";
      //i++;
    }
    b = (i+1)*stacks;
  }
  myfile.close();
  printf("Cone created!\n");

  insertTexturesName("models/shapes.xml",file);
}

void sphere(char *r,char *s,char *stack,char *file)
{
  float radius = strtof(r,0);

  float s1 = strtof(s,0);
  float s2 = strtof(stack,0);
  float x = s1*s2*8;

  int k1 = atoi(s),k2 = atoi(stack);

  float slices = (2*M_PI)/k1;
  float stacks = (M_PI)/k2;

  float a,b = 0;

  ofstream myfile;
  myfile.open(file);
  myfile << x << "\n";

  for (int i=0;i < s2;i++)
  {
    a=0;
    for(int j=0;j < s1;j++)
    {
      //bot
      myfile << radius*sin(b+stacks)*sin(a+slices) << " " << radius*cos(b+stacks) << " " << radius*sin(b+stacks)*cos(a+slices) << "\n";
      myfile << radius*sin(a+slices)*sin(b) << " " << radius*cos(b) << " " << radius*sin(b)*cos(a+slices) << "\n";
      myfile << radius*sin(b)*sin(a) << " " << radius*cos(b) << " " << radius*sin(b)*cos(a) << "\n";
      //top
      myfile << radius*sin(b)*sin(a) << " " << radius*cos(b) << " " << radius*sin(b)*cos(a) << "\n";
      myfile << radius*sin(a)*sin(b+stacks) << " " << radius*cos(b+stacks) << " " << radius*sin(b+stacks)*cos(a) << "\n";
      myfile << radius*sin(b+stacks)*sin(a+slices) << " " << radius*cos(b+stacks) << " " << radius*sin(b+stacks)*cos(a+slices) << "\n";
      a = (j+1)*slices;
    }
    b = (i+1)*stacks;
  }

  myfile.close();
  printf("Sphere created!\n");

  insertTexturesName("models/shapes.xml",file);
}

void box(char *x,char *y,char *z,char *file)
{
  float fx = strtof(x,0);
  float fy = strtof(y,0);
  float fz = strtof(z,0);

  ofstream myfile;

  myfile.open(file);
  myfile << "48\n";
  //back1
  myfile << fx << " " << -fy << " " << -fz << "\n";
  myfile << fx << " " << fy << " " << -fz << "\n";
  myfile << fx << " " << -fy << " " << fz << "\n";
  //back2
  myfile << fx << " " << -fy << " " << fz << "\n";
  myfile << fx << " " << fy << " " << -fz << "\n";
  myfile << fx << " " << fy << " " << fz << "\n";
  //front1
  myfile << -fx << " " << -fy << " " << fz << "\n";
  myfile << -fx << " " << fy << " " << -fz << "\n";
  myfile << -fx << " " << -fy << " " << -fz << "\n";
  //front2
  myfile << -fx << " " << fy << " " << -fz << "\n";
  myfile << -fx << " " << -fy << " " << fz << "\n";
  myfile << -fx << " " << fy << " " << fz << "\n";
  //ground1
  myfile << fx << " " << -fy << " " << -fz << "\n";
  myfile << fx << " " << -fy << " " << fz << "\n";
  myfile << -fx << " " << -fy << " " << fz << "\n";
  //ground2
  myfile << -fx << " " << -fy << " " << -fz << "\n";
  myfile << fx << " " << -fy << " " << -fz << "\n";
  myfile << -fx << " " << -fy << " " << fz << "\n";
  //left1
  myfile << -fx << " " << -fy << " " << fz << "\n";
  myfile << fx << " " << -fy << " " << fz << "\n";
  myfile << fx << " " << fy << " " << fz << "\n";
  //left2
  myfile << -fx << " " << fy << " " << fz << "\n";
  myfile << -fx << " " << -fy << " " << fz << "\n";
  myfile << fx << " " << fy << " " << fz << "\n";
  //top1
  myfile << fx << " " << fy << " " << fz << "\n";
  myfile << fx << " " << fy << " " << -fz << "\n";
  myfile << -fx << " " << fy << " " << fz << "\n";
  //top2
  myfile << fx << " " << fy << " " << -fz << "\n";
  myfile << -fx << " " << fy << " " << -fz << "\n";
  myfile << -fx << " " << fy << " " << fz << "\n";
  //right1
  myfile << fx << " " << -fy << " " << -fz << "\n";
  myfile << -fx << " " << -fy << " " << -fz << "\n";
  myfile << fx << " " << fy << " " << -fz << "\n";
  //right2
  myfile << -fx << " " << fy << " " << -fz << "\n";
  myfile << fx << " " << fy << " " << -fz << "\n";
  myfile << -fx << " " << -fy << " " << -fz << "\n";

  myfile.close();
  printf("Box created!\n");

  insertTexturesName("models/shapes.xml",file);
}

void plane(char *string,char *file)
{
  float s = strtof(string,0);

  ofstream myfile;

  myfile.open(file);
  myfile << "6\n";

  myfile << 1.0f*s << " " << "0.0" << " " << 1.0f*s << "\n";
  myfile << 1.0f*s << " " << "0.0" << " " << -1.0f*s << "\n";
  myfile << -1.0f*s << " " << "0.0" << " " << 1.0f*s << "\n";

  myfile << 1.0f*s << " " << "0.0" << " " << -1.0f*s << "\n";
  myfile << -1.0f*s << " " << "0.0" << " " << -1.0f*s << "\n";
  myfile << -1.0f*s << " " << "0.0" << " " << 1.0f*s << "\n";

  myfile.close();
  printf("Plane created!\n");

  insertTexturesName("models/shapes.xml",file);
}

int main(int argc,char* argv[])
{
  switch ((argv[1])[0])
  {
    case 's'://sphere
      sphere(argv[2],argv[3],argv[4],argv[5]);
      break;

    case 'p'://plane size storage
      plane(argv[2],argv[3]);
      break;

    case 'b'://box x y z storage
      box(argv[2],argv[3],argv[4],argv[5]);
      break;

    case 'c'://cone radius height slices stacks storage
      cone(argv[2],argv[3],argv[4],argv[5],argv[6]);
      break;

    default:
      break;
  }
  return 0;
}
