#include "lisagamelib.h"
#include "Physics.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Missile.h"

class MyEngine : public GameEngine {
private:
	wstring Title;
	wstring astCS;
	enum spriteID{ship,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,missile,win,lose};
	list<Asteroid> ast;
	XMFLOAT2 middle;

	Ship myShip;
	Missile m1;
public:
	MyEngine(float color[4]) : GameEngine(color, LGDK_MODE_BOTH){
		Title = L"Asteroid: ";
		astCS = Asteroid::astNum;
		SetTitleBar(Title + astCS);

		Asteroid::astNum = 0;
		//--Add 10 Asteroid Objects
		for(int x = 0; x < 10; x++){
			ast.push_back(Asteroid());
		}

		Missile m1;

		middle.x = SCREEN_WIDTH / 2;
		middle.y = SCREEN_HEIGHT / 2;
	}

	bool LoadContent(){

		spriteEng_.AddAnimatedSprite(ship, L"spaceship.png",4,7);
		spriteEng_.SetSpriteLocation(ship, myShip.position);

		for(int x = 0; x < 10; x++){
			int y = x + 1;
			spriteEng_.AddAnimatedSprite(y, L"aste.png",8,8);
		}

		spriteEng_.AddSprite(missile, L"missile.png");
		spriteEng_.AddSprite(win,L"win.jpg");
		spriteEng_.AddSprite(lose,L"lose.jpg");

		//--Set Position--
		for(auto x = ast.begin(); x != ast.end(); x++){
			spriteEng_.SetSpriteLocation(x->id, x->position);
		}

		//---set size varible==
		for(auto x = ast.begin(); x != ast.end(); x++){
			spriteEng_.SetScale(x->id, x->scale);
		}


		for(auto x = ast.begin(); x != ast.end(); x++){
			spriteEng_.GetSize(x->id,x->size);
		}

		//--Getting the Radis==Biggest Size is the diamenter==
		for(auto x = ast.begin(); x != ast.end(); x++){
			x->size.x >= x->size.y ? x->radius = x->size.x : x->radius = x->size.y;
			x->radius = x->radius / 2;
		}

		spriteEng_.GetSize(ship,myShip.size);
		myShip.size.x >= myShip.size.y ? myShip.radius = myShip.size.x : myShip.radius = myShip.size.y;
		myShip.radius = myShip.radius / 2;

		//--Scale the Ship
		XMFLOAT2 scaleship(.5,.5);
		spriteEng_.SetScale(ship,scaleship);

		//Check initial positons
		int deltah = 30;
		for(auto x = ast.begin(); x != ast.end(); x++){
			if(	(x->position.x < myShip.position.x + deltah && x->position.x > myShip.position.x + deltah)
				&&
				(x->position.y < myShip.position.y + deltah && x->position.y > myShip.position.y + deltah)	){
					x->position.x = x->position.x + 50;
					x->position.y = x->position.y + 50;
			}
		}


		return 1;
	}

	void UnloadContent(){
		spriteEng_.RemoveSprite(ship);

		for(auto x = ast.begin(); x!= ast.end(); x++){
			spriteEng_.RemoveSprite(x->id);
		}

		spriteEng_.RemoveSprite(missile);
	}

	void Update(float dt){
		astCS = to_wstring(static_cast<long long> (Asteroid::astNum));
		SetTitleBar(Title + astCS);

		if(m1.fired != true){
			spriteEng_.MoveatAngle(missile, m1.velocity.x);
		}

		//--Asteroid is not hit
		for(auto x = ast.begin(); x != ast.end(); x++){
			if  (x->destroyed != true){
				x->position.x = x->position.x + x->velocity.x;
				x->position.y = x->position.y + x->velocity.y;
				spriteEng_.SetSpriteLocation(x->id,  x->position);
				spriteEng_.PlaySprite(x->id,1,64,100);
			}
		}

		//--User Input--  ------------------------------------------------
		if(leftKey()){
			spriteEng_.SetRotation(ship,myShip.rotateLeft());
		}
		if(rightKey()){
			spriteEng_.SetRotation(ship,myShip.rotateRight());
		}
		if(upKey()){
			spriteEng_.PlaySprite(ship,1,3,50);
			spriteEng_.MoveatAngle(ship,myShip.velocity.y);
		}
		if(downKey()){
			spriteEng_.PlaySprite(ship,1,3,50);
			spriteEng_.MoveatAngle(ship,myShip.velocity.y * -1);
		}
		if(keyState(' ')){
			spriteEng_.GetSpriteLocation(ship, m1.position);
			spriteEng_.SetRotation(missile, myShip.getRot());
			spriteEng_.SetSpriteLocation(missile, m1.position);
		}

		//--Screen Teleport--------------------------------------
		if(myShip.position.x > SCREEN_WIDTH){
			myShip.position.x = 0;
			spriteEng_.MoveatAngle(ship,myShip.velocity.x);
		}
		else if (myShip.position.x < 0){
			myShip.position.x = SCREEN_WIDTH;
			spriteEng_.MoveatAngle(ship,myShip.velocity.x);
		}
		else if(myShip.position.y > SCREEN_HEIGHT){
			myShip.position.x = 0;
			spriteEng_.MoveatAngle(ship,myShip.velocity.x);
		}
		else if (myShip.position.y < 0){
			myShip.position.x = SCREEN_HEIGHT;
			spriteEng_.MoveatAngle(ship,myShip.velocity.x);
		}

		//--Asteroid Returns to screens
		for(auto x = ast.begin(); x != ast.end(); x++){
			if(x->position.y > SCREEN_HEIGHT){
				x->position.y = 0;
				spriteEng_.SetSpriteLocation(x->id,x->position);
			}
			else if (x->position.y < 0){
				x->position.y = SCREEN_HEIGHT;
				spriteEng_.SetSpriteLocation(x->id,x->position);
			}
			else if (x->position.x < 0){
				x->position.x = SCREEN_WIDTH;
				spriteEng_.SetSpriteLocation(x->id,x->position);
			}
			else if (x->position.x > SCREEN_WIDTH){
				x->position.x = 0;
				spriteEng_.SetSpriteLocation(x->id,x->position);
			}
		}

		//Ship Collision
		for(auto x = ast.begin(); x != ast.end(); x++){
			if(spriteEng_.spriteHit(ship,x->id)){
					spriteEng_.SetSpriteLocation(lose,middle);
			}
		}

		//--Missile Hit-------------------------------------
		for(auto x = ast.begin(); x != ast.end(); x++){
			if(spriteEng_.spriteHit(x->id,missile)){
				if(x->destroyed == false){
					Asteroid::astNum--;
				}
				x->destroyed = true;
				x->position.x = 3000;
				x->position.y = 3000;				
			}
		}

		//IF you win
		if(Asteroid::astNum <= 0){
			for(auto x = ast.begin(); x != ast.end(); x++){
				if(spriteEng_.spriteHit(x->id,missile)){
					x->destroyed = true;

					x->position.x = -1000;
					x->position.y = -1000;
					}
			}
			spriteEng_.SetSpriteLocation(win,middle);
		}
	}
	virtual ~MyEngine(){
	}
};

int Asteroid::astNum;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow){

	float color[4]= { 0.0f, 0.0f, 0.f, 1.0f };

	std::auto_ptr<MyEngine> gm (new MyEngine(color));

	if (!gm->InitEngine(hInstance, nCmdShow))
		return -1;

	while( gm->MessageCheck() != WM_QUIT )
	{
		// Update
		gm->Update( 0.0f );
		// Draw
		gm->Render( );
	}

	return static_cast<int>(0);

}
