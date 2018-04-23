#include "Project/CLHandler.h"

CLHandler::CLHandler()
{
	CLsetUp();
}

void CLHandler::create_prog()
{
	FILE *program_handle;
	char *program_buffer, *program_log;
	size_t program_size, log_size;

	/* Read program file and place content into buffer */
	program_handle = fopen(PROGRAM_FILE, "r");
	if (program_handle == NULL) {
		perror("Couldn't find the program file");
		exit(1);
	}
	fseek(program_handle, 0, SEEK_END);
	program_size = ftell(program_handle);
	rewind(program_handle);
	program_buffer = (char*)malloc(program_size + 1);
	program_buffer[program_size] = '\0';
	fread(program_buffer, sizeof(char), program_size, program_handle);
	fclose(program_handle);

	/* Create program from file */
	program = clCreateProgramWithSource(context, 1,
		(const char**)&program_buffer, &program_size, &err);
	if (err < 0) {
		perror("Couldn't create the program");
		exit(1);
	}
	free(program_buffer);

	/* Build program */
	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (err < 0) {

		/* Find size of log and print to std output */
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
			0, NULL, &log_size);
		program_log = (char*)malloc(log_size + 1);
		program_log[log_size] = '\0';
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
			log_size + 1, program_log, NULL);
		printf("%s\n", program_log);
		free(program_log);
		exit(1);
	}

}

void CLHandler::get_device()
{
	cl_platform_id platform;
	/* Identify a platform */
	err = clGetPlatformIDs(1, &platform, NULL);
	if (err < 0) {
		perror("Couldn't find any platforms");
		exit(1);
	}

	/* Access a device */
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1,&device, NULL);
	if (err == CL_DEVICE_NOT_FOUND) 
	{
		perror("Couldn't find any GPU's");
		err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, NULL);
		
	}
	if (err < 0)
	{
		perror("Couldn't find any devices");
	}
}

void CLHandler::CLsetUp()
{
	//get device
	get_device();
	/* Create the context */
	context = clCreateContext(NULL, 1, &device, NULL,
		NULL, &err);
	if (err < 0) {
		perror("Couldn't create a context");
		exit(1);
	}
	//Create program
	create_prog();
}

glm::vec3 CLHandler::MAT_VEC_MULT(glm::vec3 Vector, glm::mat4 Mat)
{


	float correct[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	//cast input variables into I-Values
	vec[0] = Vector.x;
	vec[1] = Vector.y;
	vec[2] = Vector.z;
	vec[3] = 1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat[j + (i * 4)] = Mat[i][j];
		}
	}
	//create correction vector
	for (i = 0; i<4; i++)
	{
		correct[0] += mat[i] * vec[i];
		correct[1] += mat[i + 4] * vec[i];
		correct[2] += mat[i + 8] * vec[i];
		correct[3] += mat[i + 12] * vec[i];
	}

	
	/* Create kernel for the mat_vec_mult function */
	kernel = clCreateKernel(program, KERNEL_FUNC, &err);
	if (err < 0) {
		perror("Couldn't create the kernel");
		exit(1);
	}

	/* Create CL buffers to hold input and output data */
	mat_buff = clCreateBuffer(context, CL_MEM_READ_ONLY |
		CL_MEM_COPY_HOST_PTR, sizeof(float) * 16, mat, &err);
	if (err < 0) {
		perror("Couldn't create a buffer object");
		exit(1);
	}
	vec_buff = clCreateBuffer(context, CL_MEM_READ_ONLY |
		CL_MEM_COPY_HOST_PTR, sizeof(float) * 4, vec, NULL);
	res_buff = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
		sizeof(float) * 4, NULL, NULL);

	/* Create kernel arguments from the CL buffers */
	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &mat_buff);
	if (err < 0) {
		perror("Couldn't set the kernel argument");
		exit(1);
	}
	clSetKernelArg(kernel, 1, sizeof(cl_mem), &vec_buff);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), &res_buff);

	/* Create a CL command queue for the device*/
	queue = clCreateCommandQueue(context, device, 0, &err);
	if (err < 0) {
		perror("Couldn't create the command queue");
		exit(1);
	}

	/* Enqueue the command queue to the device */
	work_units_per_kernel = 4; /* 4 work-units per kernel */
	err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &work_units_per_kernel,
		NULL, 0, NULL, NULL);
	if (err < 0) {
		perror("Couldn't enqueue the kernel execution command");
		exit(1);
	}

	/* Read the result */
	err = clEnqueueReadBuffer(queue, res_buff, CL_TRUE, 0, sizeof(float) * 4,
		result, 0, NULL, NULL);
	if (err < 0) {
		perror("Couldn't enqueue the read buffer command");
		exit(1);
	}

	/* Test the result */
	if ((result[0] == correct[0]) && (result[1] == correct[1])
		&& (result[2] == correct[2]) && (result[3] == correct[3]))
	{
		printf("Matrix-vector multiplication successful.\n");
		return glm::vec3(result[0], result[1], result[2]);
	}
	else
	{
		printf("Matrix-vector multiplication unsuccessful.\n");
		return glm::vec3();
	}
}