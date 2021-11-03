#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>

long long int minimum(long long a, int b)
{
	return (a < b) * a + (a >= b) * b;
}

// function for printing logical size of a file
void log_size(const char* filename)
{
        int fd = open(filename, O_WRONLY);
	// file open error handling
        if (fd < 0)
        {
		std::cout << filename << " open error" << std::endl;
                exit(-1);
        }
        int lse = lseek(fd, 0, SEEK_END);
	// lseek error handling
        if (lse < 0)
        {
                std::cout << "Offset error" << std::endl;
                exit(-1);
        }
	std::cout << filename <<  "logical is " << lse << std::endl;
	close(fd);
}

void phys_size(const char* filename)
{
        int overall_bytes = 0;
        int fd = open(filename, O_RDONLY);
	// open file error handling
        if (fd < 0)
        {
		std::cout << "Failed to open " << filename << std::endl;
                exit(-1);
        }
        bool flag = false;
        while (true)
        {
                int hole = lseek(fd, 0, SEEK_DATA);
                if (hole < 0)
                {
			std::cout << "Offset error" << std::endl;
                        exit(-1);
                }
                if (hole == 0 && flag)
                        break;
                flag = true;
                int data = lseek(fd, 0, SEEK_HOLE);
                if (data < 0)
                {
			std::cout << "Offset error";
                        exit(-1);
                }
                if (data == 0)
		{
                        break;
		}
                overall_bytes += data;
        }
	std::cout <<  filename << "physical is " << overall_bytes << std::endl;
}

int main(int argc, const char** argv)
{
	// Argument check
	if (argc != 3)
	{
		std::cout << "Ambiguous argument count" << std::endl;
		exit(-1);
	}
	log_size(argv[1]);
	phys_size(argv[1]);
	int fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
	{
		std::cout << "failed to open " << argv[1] << std::endl;
		exit(-1);
	}
	int curr_overall_bytes = 0;
	int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd2 < 0)
	{
		std::cout << "Open error " <<  argv[2] << std::endl;
		exit(-1);
	}
	long long buff_size = 1 << 20;
	bool flag = false;
	while (true)
	{
		char buff[buff_size];
		int hole1 = lseek(fd1, 0, SEEK_DATA);
		if (hole1 < 0)
		{
			std::cout << "Offset error" << std::endl;
			exit(-1);
		}
		if (hole1 == 0 && flag)
		{
			break;
		}
		curr_overall_bytes += hole1;
		int hole2 = lseek(fd2, hole1, SEEK_CUR);
		if (hole2 < 0)
		{
			std::cout << "Offset error" << std::endl;
		}
		flag = true;
		int curr_data_bytes = lseek(fd1, 0, SEEK_HOLE);
		if (curr_data_bytes < 0)
		{
			std::cout << "Offset error" << std::endl;
			exit(-1);
		}
		if (curr_data_bytes == 0)
		{
			break;
		}
		int back = lseek(fd1, curr_overall_bytes, SEEK_SET);
		if (back < 0)
		{
			std::cout << "Offset error" << std::endl;
			exit(-1);
		}
		int r_bytes = 0;
		while (r_bytes < curr_data_bytes)
		{
		int r_count = read(fd1, buff, minimum(sizeof(buff), (curr_data_bytes - r_bytes)));
		if (r_count == 0)
		{
			break;
		}
		if (r_count < 0)
		{
			std::cout << "Read error" << std::endl;
			exit(-1);
		}
		r_bytes += r_count;
		int w_count = write(fd2, buff, r_count);
		if (w_count < 0)
		{
			std::cout << "Write error" << std::endl;
			exit(-1);
		}
		}
		curr_overall_bytes += curr_data_bytes;
	}
	close(fd2);
	close(fd1);
	log_size(argv[2]);
	phys_size(argv[2]);

	return 0;
}
