#include "game.h" // including main class that includes other classes




Game::Game() {// Initialize the needed game stuff
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) cout << "Failed at SDL_Init()" << SDL_GetError() << endl;//Initialize everything
    if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren) < 0){ cout << "Failed at SDL_CreateWindowAndRenderer();" << endl;}  // Create window
    SDL_SetWindowTitle(win, "Platformer"); //Set Window Title
    TTF_Init(); // Initialize text
    loadMap("res/lvl/11.level");
    running=true; //Make our program stay on until told otherwise
    count=0; // frame counter
    font = TTF_OpenFont("res/ttfs/impact.ttf", 24); //Gets font for text
    mapX=mapY=0;
    speed = 4;
    player.setImage("res/gfx/playerwalksprite.png", ren); //Player Entity
    player.setSource(0,0, 9, 15); // Get coordinates that should be rendered    
    player.setDest(0, HEIGHT/2, 24, 32); 
    idle = player.createCycle(1, 9, 15, 2, 20); //Idle Animation Preparation
    idlel = player.createCycle(2, 9, 15, 2, 20);
    walkr = player.createCycle(3, 9, 15, 8, 7); // Walk right animation
    walkl = player.createCycle(4, 9, 15, 8, 7); // Walk left animation
    player.setCurAnimation(idle); // Sets current animation
    //theme.load("res/aud/wav/Bosstheme.wav");
		   
    loop(); // Calls loop function after program preparation
}

Game::~Game() {
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  IMG_Quit();
  SDL_Quit();
}



void Game::loop() {
	static int lastTime = 0;
  //theme.play();
	while(running) {

	  lastFrame=SDL_GetTicks();
	  if(lastFrame >= (lastTime+1000)) {
	    lastTime=lastFrame;
	    frameCount=0;

	  }
	   
	  render();
	  input();
	  update();
	}
}

void Game::render() {
  SDL_SetRenderDrawColor(ren, 126, 192, 238, 255);
  SDL_Rect rect;
  rect.x=rect.y=0;
  rect.w=WIDTH;
  rect.h=HEIGHT;
  SDL_RenderFillRect(ren, &rect);

  drawMap();
  draw("My First Platformer Lmao", 0, 0, 255, 0, 0);
  draw(player);

  frameCount++;
  int timerFPS = SDL_GetTicks()-lastFrame;
  if(timerFPS<(1000/60)) {
    SDL_Delay((1000/60)-timerFPS);
  }

  SDL_RenderPresent(ren);
}

void Game::draw(Object o) {
	SDL_Rect dest = o.getDest();
	SDL_Rect src = o.getSource();
	SDL_RenderCopyEx(ren, o.getTex(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
}

void Game::draw(const char* msg, int x, int y, int r, int g, int b) {
	SDL_Surface* surf;
	SDL_Texture* tex;
	SDL_Color color;
	color.r=r;
	color.g=g;
	color.b=b;
	color.a=255;
	SDL_Rect rect;
	surf = TTF_RenderText_Solid(font, msg, color);
	tex = SDL_CreateTextureFromSurface(ren, surf);
	rect.x=x;
	rect.y=y;
	rect.w=surf->w;
	rect.h=surf->h;
	SDL_FreeSurface(surf);
	SDL_RenderCopy(ren, tex, NULL, &rect);
	SDL_DestroyTexture(tex);
}

void Game::input() {
  SDL_Event e;
  while(SDL_PollEvent(&e)) {
    if(e.type == SDL_QUIT) {running=false; cout << "Quitting" << endl;}
    if(e.type == SDL_KEYDOWN) {
      if(e.key.keysym.sym == SDLK_ESCAPE) running=false;
      if(e.key.keysym.sym == SDLK_a) {l=1;r=0;}
      if(e.key.keysym.sym == SDLK_d) {r=1;l=0;}
      if(e.key.keysym.sym == SDLK_w) u=1;
      if(e.key.keysym.sym == SDLK_s) d=1;
      if(e.key.keysym.sym == SDLK_SPACE) if(!fall){jumping = true;}
      if(e.key.keysym.sym == SDLK_BACKSPACE) cheatfly=true;


    }
    if(e.type == SDL_KEYUP) {
      if(e.key.keysym.sym == SDLK_a) {l=0;player.setCurAnimation(idlel);}
      if(e.key.keysym.sym == SDLK_d) {r=0;player.setCurAnimation(idle);}
      if(e.key.keysym.sym == SDLK_w) u=0;
      if(e.key.keysym.sym == SDLK_s) d=0;
      if(e.key.keysym.sym == SDLK_BACKSPACE) cheatfly=false;

    }
     SDL_GetMouseState(&mousex, &mousey);
  }
}

void Game::update() {

  pymomentum =15;

  player.setDest(player.getDX(),player.getDY()+pymomentum);
  
  if(l) {if (player.getCurAnimation()!=walkl){player.setCurAnimation(walkl);}if(phase==1){player.setDest(player.getDX()-speed, player.getDY());}}
  if(r) {if(player.getCurAnimation()!=walkr) {player.setCurAnimation(walkr);}if(phase==1){player.setDest(player.getDX()+speed, player.getDY());}}
  if(jumping == true) {
    j++;

    player.setDest(player.getDX(), player.getDY()-22);
    if (j>3) {
      jumping = false;
      j=0;
      fall=1;
    }

  }

  if(cheatfly == true) {player.setDest(player.getDX(), player.getDY()-18);} 
  player.updateAnimation();
  fall=1;
  phase=1;
  for(int i=0; i<map.size(); i++) {
    if(collision(player, map[i])) {
      if (collision_type[3]){player.setDest(player.getDX(),player.getDY()-GRAV);} 
      if(map[i].getsSide()) phase=0;
       if(map[i].getId() == 35) {
        if(u) {player.setDest(player.getDX(), player.getDY()-(12*TILE_SIZE));u=d=0;}
        if(d) {player.setDest(player.getDX(), player.getDY()+(10*TILE_SIZE));u=d=0;}
      }
    }
  }
  if(phase==0) fall=1;
  
  
  if(fall) { player.setDest(player.getDX(), (player.getDY()+player.getDH())-GRAV);}
  

  if(player.getDX() < 100) {player.setDest(100, player.getDY()); scroll(speed, 0);}
  if(player.getDX() > WIDTH-100) {player.setDest(WIDTH-100, player.getDY()); scroll(-speed, 0);}
  if(player.getDY() < 100) {player.setDest(player.getDX(), 100); scroll(0, speed);}
  if(player.getDY() > HEIGHT-100) {player.setDest(player.getDX(), HEIGHT-100); scroll(0, -speed);}
}



void Game::loadMap(const char* filename) {
	Object tmp;
	tmp.setImage("res/lvl/tileset.png", ren);
	int current, mx, my, mw, mh;
	ifstream in(filename);
	if(!in.is_open()) {
	  cout << "Failed to open map file." << endl;
	  return;
	}
	in >> mw;
	in >> mh;
	in >> mx;
	in >> my;
	for(int i=0; i<mh; i++) {
	  for(int j=0; j<mw; j++) {
	    if(in.eof()) {
	      cout << "Reached end of map file too soon." << endl;
	      return;
	    }
	    in >> current;
      if(current ==0)  {tmp.setsSide(0);}
	    if(current != 0) {
	      tmp.setsTop(1);
        tmp.setsSide(0);
	      tmp.setSource((current-1)*32, 0, 32, 32);
	      tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
	      tmp.setId(current);
	      //if (current==42) tmp.setsTop(0);
        if(current==51 || current==50) tmp.setsSide(1);
        
	      map.push_back(tmp);
	    } 
	  }
	}
	in.close();
}

void Game::scroll(int x, int y) {
  for(int i=0; i<map.size(); i++) {
    map[i].setDest(map[i].getDX()+x, map[i].getDY()+y);
  }
}



void Game::drawMap() {
  for(int i=0; i<map.size(); i++) {
    if(map[i].getDX() >= mapX-TILE_SIZE
    & map[i].getDY() >= mapY-TILE_SIZE
    & map[i].getDX() <= mapX+WIDTH+TILE_SIZE
    & map[i].getDY() <= mapY+HEIGHT+TILE_SIZE) {
      draw(map[i]);
    }
  }
}

bool Game::collision(Object a, Object b) {
  collision_type[0]=false;
  collision_type[1]=false;
  collision_type[2]=false;
  collision_type[3]=false;
  int aleft, aright, atop, abottom;
  int bleft, bright, btop, bbottom;
  aleft = a.getDX(); aright = a.getDX() + a.getDW(); atop = a.getDY(); abottom=a.getDY() + a.getDH();
  bleft = b.getDX(); bright = b.getDX() + b.getDW(); btop = b.getDY(); bbottom=b.getDY() + b.getDH();
  if (aleft < bright){collision_type[0]= true;return collision_type[0];}
  if (aright > bleft){collision_type[1]= true;return collision_type[1];}
  if (atop < bbottom){collision_type[2]= true;return collision_type[2];}
  if (abottom > btop){collision_type[3]= true;return collision_type[3];}
}









