import ddf.minim.*;
import processing.serial.*;
PFont arcade;

Minim minim;
AudioPlayer bgmusic, scoremusic, winmusic,losemusic;

Serial myPort;
String ms = "";
//String gameStart = "";
int score;
int time ;
String gameEnd = "";
int[] input = {10, 0};

boolean ready = false;
boolean gameStart = false;
boolean timeStart = false;
boolean showScore = false;
boolean lose = false;
boolean win = false;
boolean restart = false;

void setup() {
  background(0);
  size(1920, 1080);
  arcade = loadFont("Erbos-Draco-1st-Open-NBP-96.vlw");

  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');

  //ready = true;
  minim = new Minim(this);
  bgmusic = minim.loadFile("aeroband.mp3",1024);
  scoremusic = minim.loadFile("coin.wav",1024);
}

void draw() {
  //bgmusic.play();
  
  if (ms.equals("ready")) {
    ready = true;
  } 
  
  if (ms.equals("s")) {
    //println("start!!!!!!!!!!");
    ready = false;
    gameStart = true;
    //scoreStart = true;
  }
  
  if (ms.equals("w")) {
    gameStart = false;
    lose = false;
    win = true;
  }
  if (ms.equals("l")) {
    gameStart = false;
    win = false;
    ready = false;
    lose = true;
  }
  if (ms.equals("r")){
    lose = false;
    win = false;
    ready = true;
  }

  if (ready) {
    //background(255, 100, 255);
    background(0);
    textFont(arcade, 48);
    fill(244, 20, 89);
    text("Ready?", 200, 200);
    text("Pink Button", 500, 400);

    textFont(arcade, 32);
    fill(255);
    text("push the", 200, 400);
    text("to start", 1040, 400);
  }

  if (gameStart) {
    ////color(244, 20, 89);
    //fill(244, 20, 89);
    background(255, 100, 255);
    //background(0);
    textFont(arcade, 36);
    text("time: "+time, 820, 140);

    textFont(arcade, 200);
    text(score, 860, 580);
  }

  if (lose) {
    background(50,0,50);
    textFont(arcade, 48);
    fill(255);
    text("try one more time!", 460, 400);
  }

  if (win) {
    background(244, 20, 89);
    textFont(arcade, 48);
    fill(0);
    text("Congrats!!!", 500, 200);
    text("Pink Button", 500, 400);
    text("to restart!", 1040, 400);
  }
}

void serialEvent(Serial myPort) {
  String message = myPort.readStringUntil('\n'); 

  if (message != null) {
    message = trim(message);
    //String[] input = split(message, ',');
    
    ms = message;
    String[] data = split(ms, ',');
    for (int i = 0; i <data.length; i++) {
      input[i] = int(data[i]);
    }
    
    println(ms);
    time = input[0];
    score = input[1];
  }
}