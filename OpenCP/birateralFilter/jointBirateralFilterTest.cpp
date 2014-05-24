#include "../opencp.hpp"
#include <fstream>
using namespace std;

void guiJointBirateralFilterTest(Mat& src, Mat& guide)
{
	Mat dest,dest2;

	string wname = "joint birateral filter";
	namedWindow(wname);

	int a=0;createTrackbar("a",wname,&a,100);
	int sw = 0; createTrackbar("switch",wname,&sw, 1);
	int r = 20; createTrackbar("r",wname,&r,200);
	int space = 200; createTrackbar("space",wname,&space,2000);
	int color = 300; createTrackbar("color",wname,&color,2550);
	int key = 0;
	Mat show;

	while(key!='q')
	{
		cout<<"r="<<r<<": "<<"please change 'sw' for changing the type of implimentations."<<endl;
		double sigma_color = color/10.0;
		double sigma_space = space/10.0;
		int d = 2*r+1;

		
		if(sw==0)
		{
			CalcTime t("birateral filter: opencv");
			jointBilateralFilter(src, guide, dest, Size(d,d), sigma_color, sigma_space);
		}
		if(sw==1)
		{
			CalcTime t("birateral filter: fastest opencp implimentation");
			jointBilateralFilter(guide, src, dest, Size(d,d), sigma_color, sigma_space);
		}

		patchBlendImage(src,dest,dest,Scalar(255,255,255));
		alphaBlend(src, dest,a/100.0, show);
		imshow(wname,show);
		key = waitKey(1);
	}
}

/*
void timeBirateralTest(Mat& src)
{
	int iteration = 10;
	Mat dest;

	ofstream out("birateraltime.csv");

	double time_opencv;
	double time_opencp;
	double time_opencp_sp;
	double time_opencp_sl;
	for(int r=0;r<200;r++)
	{
		cout<<"r:"<<r<<" :";
		int d = 2*r+1;
		double sigma_color = 30.0;
		double sigma_space = d/3.0;

		{
			Stat st;
			for(int i=0;i<iteration;i++)
			{
				CalcTime t("time",TIME_SEC,false);
				bilateralFilter(src, dest, d, sigma_color, sigma_space);
				st.push_back(t.getTime());
			}
			time_opencv=st.getMedian();
		}

		{
			Stat st;
			for(int i=0;i<iteration;i++)
			{
				CalcTime t("time",TIME_SEC,false);
				bilateralFilter(src, dest, Size(d,d), sigma_color, sigma_space, BILATERAL_DEFAULT);
				st.push_back(t.getTime());
			}
			time_opencp=st.getMedian();
		}

		{
			Stat st;
			for(int i=0;i<iteration;i++)
			{
				CalcTime t("time",TIME_SEC,false);
				bilateralFilter(src, dest, Size(d,d), sigma_color, sigma_space, BILATERAL_SEPARABLE);
				st.push_back(t.getTime());
			}
			time_opencp_sp=st.getMedian();
		}

		{
			Stat st;
			for(int i=0;i<iteration;i++)
			{
				CalcTime t("time",TIME_SEC,false);
				bilateralFilter(src, dest, Size(d,d), sigma_color, sigma_space, BILATERAL_SLOWEST);
				st.push_back(t.getTime());
			}
			time_opencp_sl=st.getMedian();
		}

		out<<time_opencv<<","<<time_opencp<<","<<time_opencp_sp<<","<<time_opencp_sl<<endl;
		cout<<time_opencv<<","<<time_opencp<<","<<time_opencp_sp<<","<<time_opencp_sl<<","<<endl;
	}
}
*/