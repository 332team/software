#include <iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")


int main()
{
	//����ͼ��
	GDALDataset* poSrcDS;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ��Ŀ�Ⱥ͸߶�

	int StartX1 = 100, StartY1 = 100;
	//�����Ⱥ͸߶�
	int tmpXlen1 = 100, tmpYlen1 = 50;
	int imgXlen, imgYlen;
	//��ʼλ������
	int StartX2 = 500, StartY2 = 500;
	//�����Ⱥ͸߶�
	int tmpXlen2 = 50, tmpYlen2 = 100;
	//����ͼ��·��
	char* srcPath = "trees.jpg";
	//���ͼ��·��
	char* dstPath = "res.tif";
	//ͼ���ڴ�洢,�ı������ڴ�洢
	GByte* buffTmp, *buffTmp1;
	//ͼ�񲨶���
	int i, j, bandNum;
	//ע������
	GDALAllRegister();
	//��ͼ��
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);
	//��ȡͼ��Ŀ�ȣ��߶ȺͲ�����
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();

	//����ͼ��Ŀ�Ⱥ͸߶ȷ����ڴ�
	buffTmp1 = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath, imgXlen, imgYlen, bandNum, GDT_Byte, NULL);
	//��ͼƬ������½���ͼƬ
	for (i = 0; i < bandNum; i++)
	{
		poSrcDS->GetRasterBand(i + 1)->RasterIO(
			GF_Read, 0, 0, imgXlen, imgYlen, buffTmp1, imgXlen, imgYlen, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(i + 1)->RasterIO(
			GF_Write, 0, 0, imgXlen, imgYlen, buffTmp1, imgXlen, imgYlen, GDT_Byte, 0, 0);


	}
	//�����ڴ�
	buffTmp = (GByte*)CPLMalloc(tmpXlen1*tmpYlen1 * sizeof(GByte));
	//��ȡ��ɫͨ��������buffTmp�У�ֻ��Ϊ�˻�ȡ������
	for (int n = 0; n < 3; n++)
	{
	poSrcDS->GetRasterBand(n+1)->RasterIO(GF_Read, StartX1, StartY1, tmpXlen1, tmpYlen1, buffTmp, tmpXlen1, tmpYlen1, GDT_Byte, 0, 0);
	//���ζ�ȡ����ͨ��������
	//�������򣬽��½�ͼƬ������ı���ɫ
	for (j = 0; j < tmpYlen1; j++)
		for (i = 0; i < tmpXlen1; i++)
		{
			buffTmp[j * tmpXlen1 + i] = (GByte)255;
		}
	poDstDS->GetRasterBand(n+1)->RasterIO(GF_Write, StartX1, StartY1, tmpXlen1, tmpYlen1, buffTmp, tmpXlen1, tmpYlen1, GDT_Byte, 0, 0);

	}
	buffTmp = (GByte*)CPLMalloc(tmpXlen2*tmpYlen2 * sizeof(GByte));
	//��ȡ��ɫͨ��������buffTmp�У�ֻ��Ϊ�˻�ȡ������
	for (int n = 0; n < 3; n++)
	{
		poSrcDS->GetRasterBand(n + 1)->RasterIO(GF_Read, StartX2, StartY2, tmpXlen2, tmpYlen2, buffTmp, tmpXlen2, tmpYlen2, GDT_Byte, 0, 0);
		//���ζ�ȡ����ͨ��������
		//�������򣬽��½�ͼƬ������ı���ɫ
		for (j = 0; j < tmpYlen2; j++)
			for (i = 0; i < tmpXlen2; i++)
			{
				buffTmp[j * tmpXlen2 + i] = (GByte)0;
			}
		poDstDS->GetRasterBand(n + 1)->RasterIO(GF_Write, StartX2, StartY2, tmpXlen2, tmpYlen2, buffTmp, tmpXlen2, tmpYlen2, GDT_Byte, 0, 0);

	}
	//poSrcDS->GetRasterBand(2)->RasterIO(GF_Read, StartX1, StartY1, tmpXlen1, tmpYlen1, buffTmp, tmpXlen1, tmpYlen1, GDT_Byte, 0, 0);

	



	//����ڴ�
	CPLFree(buffTmp);
	CPLFree(buffTmp1);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);
	system("PAUSE");
	return 0;
}
