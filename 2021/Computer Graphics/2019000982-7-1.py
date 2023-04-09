import glfw
from OpenGL.GL import *
import numpy as np
from OpenGL.GLU import *

gCamAng = 0
gCamHeight = 1.
gVertexArrayIndexed = None
gIndexArray = None

def createVertexAndIndexArrayIndexed():
    varr = np.array([
        (0, 0, 0),
        (0, 0, 1.5),
        (0, 1.5, 0),
        (1.5, 0, 0),
        ], 'float32')

    iarr = np.array([
        (0, 1, 2),
        (0, 2, 3),
        (0, 3, 1),
        ])
                    
    return varr, iarr

def render():
    global gCamAng, gCamHeight
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
    glEnable(GL_DEPTH_TEST)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)

    glLoadIdentity()
    gluPerspective(45, 1, 1, 10)
    gluLookAt(5*np.sin(gCamAng), gCamHeight, 5*np.cos(gCamAng), 0,0,0, 0,1,0)

    drawFrame()
    glColor3ub(255, 255, 255)

    drawCube_glDrawElemnets()

def drawCube_glDrawElements():
    global gvertexArrayIndexed, gIndexArrray
    varr = gVertexArrayIndexed
    iarr = gIndexArray
    glEnableClientState(GL_VERTEX_ARRAY)
    glVertexPointer(3, GL_FLOAT, 3*varr.itemsize, varr)
    glDrawElements(GL_TRIANGLES, iarr.size, GL_UNSIGNED_INT, iarr)
    
def drawFrame():
    glBegin(GL_LINES)
    glColor3ub(255, 0, 0)
    glVertex3fv(np.array([0., 0., 0.]))
    glVertex3fv(np.array([1., 0., 0.]))
    glColor3ub(0, 255, 0)
    glVertex3fv(np.array([0., 0., 0.]))
    glVertex3fv(np.array([0., 1., 0.]))
    glColor3ub(0, 0, 255)
    glVertex3fv(np.array([0., 0., 0.]))
    glVertex3fv(np.array([0., 0., 1.]))
    glEnd()

def main():
    global gVertexArrayIndexed, gIndexArray
    
    if not glfw.init():
        return
    window = glfw.create_window(480, 480, '2019000982-7-1', None, None)
    if not window:
        glfw.terminate()
        return
    glfw.make_context_current(window)

    gVertexArrayIndexed, gIndexArray = createVertexAndIndexArrayIndexed()

    while not glfw.window_should_close(window):
        glfw.poll_events()
        render()
        glfw.swap_buffers(window)

    glfw.terminate()

if __name__ =="__main__":
    main()

    
    
