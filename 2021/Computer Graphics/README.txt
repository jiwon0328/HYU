# PA2
## Cow Rollercoaster

### global variables
- firstPos : this is an array that store the first position
- cawCount : this is the variable that store the number of cows
- cowsPos : this is an array that store the positions of cows
- isNotInitialClick : this is an variable that indicates whether the click is initial or not
- returnCow : this is an array that store the head direction with cow's position
- timeStart : this is the variable that indicate whether the cow is rotating or not

### catmullRomSpline
- this is a function that caculate the catmull-rom spline

### getHeadDir
- this is a function that return the head direction of spline by derivation
- this uses Euler Angles and use atan to find angles
- it returns the direction of the cow

### TODO in display
- this draws the cow if the number of cow is lower than 6
- or rotate the cow 3 circles
- during the rotation calculate the rotating time(t) with glfw.get_time()
- if t is lower than 18  calculate the spline and head direction
- there are 6 types of spline during 3 rotations 
- with this spline and direction, draw the cow of that clock time
- after the 18 clock times reset the variables and place the cow to the first position

### onMouseButton
- add return if cowCount is 6 to prevent the mouse click during the rotation
- when user drag the mouse holizontal make isNotInitialClick plus 1
- this part makes the copy of cow in UI if user double clicked the cow

### TODO in onMouseDrag
- also add some parts to prevent the mouse click during the rotation
- by referring the horizontal dragging wrote this part
- in here, use the intersection of cowPickPosition and z plane
- this part makes the cow just move up and down and don't move horizentaly
