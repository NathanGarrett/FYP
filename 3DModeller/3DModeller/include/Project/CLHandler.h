#pragma once
#define PROGRAM_FILE "./res/Calc.cl"
#define KERNEL_FUNC  "matvec_mult"
#include <stdlib.h>
#include <stdio.h>
#include <sys\types.h>
#include <CL\cl.h>
#include <GLM\glm.hpp>
#include <fstream>

class CLHandler
{
public:
	CLHandler();
	~CLHandler() 
	{	/* Deallocate resources */
		clReleaseMemObject(mat_buff);
		clReleaseMemObject(vec_buff);
		clReleaseMemObject(res_buff);
		clReleaseKernel(kernel);
		clReleaseCommandQueue(queue);
		clReleaseProgram(program);
		clReleaseContext(context);
	};
	
	void create_prog();
	void get_device();
	void CLsetUp();

	glm::vec3 MAT_VEC_MULT(glm::vec3 Vector, glm::mat4 Mat);

private:
	/* Host/device data structures */
	cl_device_id device;
	cl_context context;
	cl_command_queue queue;
	cl_int i, err;
	/* Program/kernel data structures */
	cl_program program;
	cl_kernel kernel;
	/* Data and buffers */
	float mat[16], vec[4], result[4];
	cl_mem mat_buff, vec_buff, res_buff;
	size_t work_units_per_kernel;
};