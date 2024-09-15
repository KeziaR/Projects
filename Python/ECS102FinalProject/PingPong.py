#Ping Pong
#PingPong.py
#Kezia Regis
#Knregis@syr.edu
#Creates a simulation of a ping pong game for one player

from graphics import*
import random

#Setting Up window
def setUpWindow():#(GW)
   win=GraphWin("Ping Pong", 800,500)
   win.setCoords(0,0, 8,5)
   win.setBackground("Black")
   return win
###########Class movecirc############
class movecirc:
# The constructor of this class contains the color, center of the circle
# and movmemnts in the x(left) and y(right) direction
   def __init__(self,center,color,color2,dx=1,dy=1):
       self.circle = Circle(center, .1)
       self.circle.setFill(color)
       self.circle.setOutline(color2)
       self.directionx = dx
       self.directiony = dy
       self.score = 0
       self.level = 1


# This fucntion is used to draw the circle onto the screen
   def drawcirc(self,win):
       self.circle.draw(win)
# This function is used to get the center of the circle and
# y coordinate to create boundaries that the ball can not pass.
# Then it will move in the opposite direction when
# self.direction is called
   def move(self,paddle):
       if self.circle.getCenter().getY() >= 5:
            self.directiony = -1
       elif self.circle.getCenter().getY() <= 0:
           self.directiony = 1
       if self.circle.getCenter().getX() >= 8:
           self.directionx = -1
       elif self.circle.getCenter().getX() <= 0:
           self.directionx = 1
           if self.directiony > self.circle.getCenter().getX() < self.directionx > self.circle.getCenter().getX():
            self.score += 1
            self.directionx = 1
       self.circle.move(self.directionx, self.directiony)



# This function displays the score of the ball when it hit the paddle
   def displayscore(self):
       score = self.score
       scoretxt = Text(Point(.8, 4.8), "Score:"+(str(score)))
       scoretxt.setFace('courier')
       scoretxt.setFill("white")
       scoretxt.setSize(20)
       scoretxt.draw(win)
       return scoretxt

#After reading the score from the previous function
# This function draws the score onto the screen
   def newscore(self,scoretxt):
       score = self.score
       scoretxt.setText("Score:"+(str(score)))

# I was trying to do levels but I decided that the game would run until the score hit 44
# To change the game a bit, I did random background colors for every eleventh point.
   def levels(self,win): #(RND)
    r = random.randrange(0,255)
    g =random.randrange(0,255)
    b =random.randrange(0,255)
    color = color_rgb(r,g,b)
    if self.score == 11:
       self.level += 1
       win.setBackground(color)
    if self.score == 22:
       self.level += 1
       win.setBackground(color)
    if self.score == 33:
       self.level += 1
       win.setBackground(color)
    if self.score == 44:
       self.level += 1
       while True:
           win.close()
           break
       win.setBackground(color)
#############end of class movecirc#################

##########Class movesqrt############
class movesqrt:
# Setting up the paddles using a constructor that has the upper and lower
# points of the rectangle as well as the color of the object
   def __init__(self,color,color2,ux,uy,bx,by):
       self.uplft = ux
       self.upight =uy
       self.botlft = bx
       self.botight = by
       self.rect = Rectangle(Point(ux,uy),Point(bx,by))
       self.rect.setFill(color)
       self.rect.setOutline(color2)
# This fucntion is used to draw the rectangle onto the screen
   def drawsqrt(self, win):
       self.rect.draw(win)
#Here we want the rectangle to move either to the right of the left
#so there are x and y coordinated in the move function
   def move(self,dx,dy):
       self.rect.move(dx,dy)
##############end of class movesqrt#################

#######Class screens############################
class Screens: #(CLOD)
#This class was created for the other two screens since they correlate with one another
    def __init__(self,dx=2,dy=4.3):
       self.x = dx
       self.y = dy

# This is the first page which contains the entrybox that saves the user's name
# and sends it to the next page.
    def page1display(self):
        pg1 = GraphWin("Welcome!", 500, 500)
        pg1.setCoords(0, 0, 5, 5)
        pg1.setBackground("gray")

        entry = Entry(Point(2, 2.5), 11)
        entry.setText("Enter a name") #(OTXT)
        entry.draw(pg1)
        entry.setFill("lightgray")


        button = Rectangle(Point(2.6, 2.63), Point(3.1, 2.35))
        button.setFill("lightgray")
        button.draw(pg1)

        buttonLabel = Text(Point(2.85, 2.5), "Enter")
        buttonLabel.draw(pg1)
        pg1.getMouse()

        name = Text(Point(2.45, 3), "Welcome")
        name.draw(pg1)
        while True:
            name.setText("Welcome!  " + entry.getText() + "  Ready to play a game of Ping Pong?")
            pg1.getMouse() #(IMS)
            pg1.close()
            return entry.getText()

#The first page has given the name in the entry box
#and has appended it to a file
    def filename(self):
       call = self.page1display() #(IEB)
       infile = open("inrecord", "r") #(IFL)
       contentsList = infile.readlines()
       infile.close()

       contentsList.append(call)
       move = contentsList
       # del move[0]

       outfile = open("inrecord", "a") #(OFL)
       for i in move: #(LOOD)
        print("{0:>28}".format(i.strip()),file=outfile)
        # print(i,file=outfile)
       outfile.close()

# This is the second page that displays the names based on the order of the name given
    def page2display(self):
        pg2 = GraphWin("Records",500,500)
        pg2.setCoords(0, 0, 5, 5)
        pg2.setBackground("gray")
        Title1 = Text(Point(2.5,4.5),"Heading").draw(pg2)
        Title1.setFill("Black")
        Title2 =Text(Point(2.5, 4.30), "Name").draw(pg2)
        Title2.setFill("Black")

        infile = open("inrecord","r")
        plus = 0
        for line in infile:
            plus += .25
            Text(Point(self.x,self.y - plus),line).draw(pg2)
        infile.close()
        #if adding another variable make sure that it increments itself so that it does not write ontop of each other
        while True:
            pg2.getMouse()
            pg2.close()
            return pg2
##############end of class screens#################

if __name__=='__main__':
# These are the functions in the Screen class
    scr = Screens() #(CLOD)

    scr.filename()

    pg2 = scr.page2display() #(FNC)

# The Ping Pong game
    win = setUpWindow()
    paddle = movesqrt("white", "gray", 0, 2, .10, 1)
    paddle.drawsqrt(win)
    bpoint = Point(.20, 5)
    ball = movecirc(bpoint, "white", "gray")
    ball.drawcirc(win)

# This control the speed, placement, and movement based on the keys
    scoretxt = ball.displayscore()
    while True:
        movement = win.checkKey()
        if movement == 'w':
            paddle.move(0,.7)
            time.sleep(.02)
        if movement == 's':
            paddle.move(0, -.7)
            time.sleep(.10)
        if win.checkKey() != 'q':
            time.sleep(.01)
            ball.move(paddle)
            ball.newscore(scoretxt)
            ball.levels(win)
