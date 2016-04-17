#pragma once

#include "HuffmanTree.h"
#include<algorithm>


typedef long LongType;


struct FileInfo
{
	unsigned char _ch;
	LongType   _count;
	string      _code;

	FileInfo(unsigned char ch = 0)
		:_ch(ch)
		, _count(0)
	{}

	FileInfo operator+(FileInfo& fi)
	{
		FileInfo tmp;
		tmp._count = this->_count + fi._count;
		return tmp;
	}

	bool operator < (FileInfo& fi)
	{
		return this->_count < fi._count;
	}

	bool operator != (const FileInfo& fi)const
	{
		return this->_count != fi._count;
	}

};

template<class T>
class FileCompress
{
public:
	FileCompress()
	{
		for (int i = 0; i < 256; ++i)
		{
			_infos[i]._ch = i;
		}
	}
public:

	void GenerateHuffmanCode()
	{
		HuffmanTree<FileInfo> hft;
		hft.CreatTree(_infos, 256 ,FileInfo());
		_GenerateHuffmanCode(hft.GetRootNode());
	}

	bool Compress(const char* filename)
	{
		//1.打开文件，统计文件字符出现的次数
		assert(filename);
		FILE* fOut = fopen(filename, "r");
		assert(fOut);

		char ch = fgetc(fOut);

		while (ch != EOF)
		{
			_infos[ch]._count++;
			ch = fgetc(fOut);
		}		

		//2.生成对应的huffman编码
		GenerateHuffmanCode();

		//3.压缩文件
		string compressFile = filename;
		compressFile += ".huffman";
		FILE* fwcompress = fopen(compressFile.c_str(), "w");
		assert(fwcompress);

		fseek(fOut, 0, SEEK_SET);
		ch = fgetc(fOut);
		char inch = 0;
		int index = 0;
		while (ch != EOF)
		{
			string& code = _infos[(unsigned char)ch]._code;
			for (size_t i = 0; i < code.size(); ++i)
			{
				inch = inch << 1;
				if (code[i] == '1')
				{
					inch |= 1;
				}
				if (++index == 8)
				{
					fputc(inch, fwcompress);
					inch = 0;
					index = 0;
				}
			}
			ch = fgetc(fOut);
		}

		if (index)
		{
			inch = inch << (8 - index);
			fputc(inch, fwcompress);
		}

		//4.配置文件，方便后续的解压缩
		string configFile = filename;
		configFile += ".config";
		FILE *fconfig = fopen(configFile.c_str(), "w");
		assert(fconfig);



		return true;
	}

	bool UnCompresss()
	{

		return true;
	}

public:

	void _GenerateHuffmanCode(HuffmanTreeNode<FileInfo>* root)
	{
		if (root == NULL)
		{
			return;
		}

		_GenerateHuffmanCode(root->_left);
		_GenerateHuffmanCode(root->_right);

		if (root->_left == NULL && root->_right == NULL)
		{
			HuffmanTreeNode<FileInfo>* cur = root;
			HuffmanTreeNode<FileInfo>* parent = cur->_parent;
			string& code = _infos[cur->_weight._ch]._code;

			while (parent)
			{
				if (parent->_left == cur)
				{
					code += '0';
				}
				else if (parent->_right == cur)
				{
					code += '1';
				}
				cur = parent;
				parent = cur->_parent;
			}

			reverse(code.begin(), code.end());
		}
	}

private:
	FileInfo _infos[256];
};

void TestFileCompress()
{
	FileCompress<FileInfo> fc;
	fc.Compress("test.txt");
}

