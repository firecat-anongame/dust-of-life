#include <iostream>
#include <vector>
#include "include/irrlicht.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

class MyEventReceiver : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			switch(event.MouseInput.Event)
			{
			case EMIE_LMOUSE_PRESSED_DOWN:
				MouseState.LeftButtonDown = true;
				break;

			case EMIE_LMOUSE_LEFT_UP:
				MouseState.LeftButtonDown = false;
				break;

			case EMIE_MOUSE_MOVED:
				MouseState.Position.X = event.MouseInput.X;
				MouseState.Position.Y = event.MouseInput.Y;
				break;

			default:
				// We won't use the wheel
				break;
			}
		}

		return false;
	}

	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	MyEventReceiver()
	{
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}
	/// /////////////////////////////////////////////

	struct SMouseState
	{
		core::position2di Position;
		bool LeftButtonDown;
		SMouseState() : LeftButtonDown(false) { }
	} MouseState;

	const SMouseState & GetMouseState(void) const
	{
		return MouseState;
	}

private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

struct myIrrlicht_
{
    IrrlichtDevice *device;
    IVideoDriver* driver;
	ISceneManager* smgr;
	IGUIEnvironment* guienv;

	MyEventReceiver receiver;
	//ICameraSceneNode* camera;

    ITexture *Tmap1;
    ITexture *Tloli;
    ITexture *Tface;
    ITexture *Tescape;
    ITexture *Tgui;
    ITexture *Tmob1;
    ITexture *TcursorMagik;


    int create()
    {
        device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(800, 600), 16,
			false, false, false, &receiver);

        if (!device)
        {
            cout<<"error: irrlicht_1\n";
            return 1;
        }

        device->setWindowCaption(L"");

        driver = device->getVideoDriver();
        smgr = device->getSceneManager();
        guienv = device->getGUIEnvironment();


        Tmap1=driver->getTexture("resource/map1.png");
        //driver->makeColorKeyTexture(Tmap1, core::position2d<s32>(0,0));

        Tloli=driver->getTexture("resource/ch1.png");
        driver->makeColorKeyTexture(Tloli, core::position2d<s32>(0,0));

        Tface=driver->getTexture("resource/face.png");
        //driver->makeColorKeyTexture(Tloli, core::position2d<s32>(0,0));

        Tescape=driver->getTexture("resource/escape.png");
        driver->makeColorKeyTexture(Tescape, core::position2d<s32>(0,0));

        Tgui=driver->getTexture("resource/gui.png");
        driver->makeColorKeyTexture(Tgui, core::position2d<s32>(0,0));

        Tmob1=driver->getTexture("resource/slime.png");
        driver->makeColorKeyTexture(Tmob1, core::position2d<s32>(0,0));

        TcursorMagik=driver->getTexture("resource/cursorMagik.png");
        driver->makeColorKeyTexture(TcursorMagik, core::position2d<s32>(0,0));

        return 0;
    }

    void removeIr()
    {
        device->drop();
    }

    void sceneStart()
    {
        driver->beginScene(true, true, SColor(255,0,0,0));
    }
    void sceneEnd()
    {
        smgr->drawAll();
		guienv->drawAll();
        driver->endScene();
    }
};

void myDrawF(IVideoDriver* dr, ITexture *tt, int x, int y, int rx2, int ry2)
{
    dr->draw2DImage(tt,
        core::position2d<s32>(x,y),
        core::rect<s32>(0,0,rx2,ry2), 0,
        video::SColor(255,255,255,255), true);
}
