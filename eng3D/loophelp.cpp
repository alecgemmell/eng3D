#include <loophelp.h>
void drawObjects(GLuint MatrixID, glm::mat4 MVP, GLuint vertexbuffer, GLuint colorbuffer, int vcount) {
	//MVP setup
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	//vertex setup stuff
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//color setup stuff
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//draw call
	glDrawArrays(GL_TRIANGLES, 0, vcount);

	//cleanup
	glDisableVertexAttribArray(0);
	return;
}