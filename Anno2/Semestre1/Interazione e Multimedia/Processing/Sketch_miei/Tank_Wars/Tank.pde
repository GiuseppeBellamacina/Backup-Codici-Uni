int b=75, h=100;
float [] gunPos = new float [2];

class Tank {
  int posX, posY, speed;

  Tank(int posX, int posY, int speed) {
    this.posX=posX;
    this.posY=posY;
    this.speed=speed;
  }

  void move() {
    if (keyPressed) {
      switch(key) {
      case 'a':
      case 'A':
        posX-=speed;
        break;
      case 'd':
      case 'D':
        posX+=speed;
        break;
      case 'w':
      case 'W':
        posY-=speed;
        break;
      case 's':
      case 'S':
        posY+=speed;
        break;
      }
    }
  }

  void displayTank() {
    noStroke();
    fill(#1C982F);
    rect(posX, posY, b, h);
  }

  void getGunPos() {
    // fare la formula che data un segmento con estremi il centro
    // del carro e il mouse e che metta x e y nell'array gunPos
  }

  void displayGun() {
    stroke(255);
    strokeWeight(20);
    line(posX+b/2, posY+h/2, gunPos[0], gunPos[1]);
  }

  void display() {
    displayTank();
    displayGun();
  }

  void run() {
    move();
    display();
  }
}
