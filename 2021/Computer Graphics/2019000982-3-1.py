import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np
TYPE = 4

# compute the positions of vertexes
points = np.zeros((12, 2), dtype = 'float')
for i in range(0, 12):
    x = np.cos(np.deg2rad(30 * i))
    y = np.sin(np.deg2rad(30 * i))
    points[i][0] = x
    points[i][1] = y
        
def render():
    global TYPE
    global points

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()

    if TYPE == 1:
        glBegin(GL_POINTS)
    elif TYPE == 2:
        glBegin(GL_LINES)
    elif TYPE == 3:
        glBegin(GL_LINE_STRIP)
    elif TYPE == 4:
        glBegin(GL_LINE_LOOP)
    elif TYPE == 5:
        glBegin(GL_TRIANGLES)
    elif TYPE == 6:
        glBegin(GL_TRIANGLE_STRIP)
    elif TYPE == 7:
        glBegin(GL_TRIANGLE_FAN)
    elif TYPE == 8:
        glBegin(GL_QUADS)
    elif TYPE == 9:
        glBegin(GL_QUAD_STRIP)
    elif TYPE == 0:
        glBegin(GL_POLYGON)
    
    for i in range(0, 12):
        glVertex2f(points[i][0], points[i][1])

    glEnd()

def key_callback(window, key, scancode, action, mods):
    global TYPE

    if key == glfw.KEY_1 and action == glfw.PRESS:
        TYPE = 1
    elif key == glfw.KEY_2 and action == glfw.PRESS:
        TYPE = 2
    elif key == glfw.KEY_3 and action == glfw.PRESS:
    	TYPE = 3
    elif key == glfw.KEY_4 and action == glfw.PRESS:
    	TYPE = 4  
    elif key == glfw.KEY_5 and action == glfw.PRESS:
    	TYPE = 5   
    elif key == glfw.KEY_6 and action == glfw.PRESS:
    	TYPE = 6  
    elif key == glfw.KEY_7 and action == glfw.PRESS:
    	TYPE = 7   
    elif key == glfw.KEY_8 and action == glfw.PRESS:
    	TYPE = 8   	
    elif key == glfw.KEY_9 and action == glfw.PRESS:
    	TYPE = 9   
    elif key == glfw.KEY_0 and action == glfw.PRESS:
    	TYPE = 0

def main():
    if not glfw.init():
        return
    window = glfw.create_window(480, 480, "2019000982-3-1", None, None)

    if not glfw.init():
        glfw.terminate()
        return

    glfw.set_key_callback(window, key_callback)

    glfw.make_context_current(window)

    while not glfw.window_should_close(window):
        glfw.poll_events()
        render()
        glfw.swap_buffers(window)

    glfw.terminate()

if __name__ == "__main__":
    main()

        
    
