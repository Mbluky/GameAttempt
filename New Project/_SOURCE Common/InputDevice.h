#ifndef INPUT_DEVICE
#define INPUT_DEVICE

#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include <Windows.h>
#include <string.h>
#include <vector>
#include <memory>
#include <array>
#include <queue>
#include <assert.h>

#include "../_SOURCE Common/Vectors.h"

class Gamepad
{
public:

	enum Type
	{
		Button,
		Axis,
		Stick,
		Invalid
	};

	enum StickType : int
	{
		Dpad = 0,
		Analog1 = 1,
		Analog2 = 2
	};

	class Event
	{
		const Type type;
		const int index;
		const union
		{
			struct
			{
				Vector2D pos;
			};
			float val;
			bool pressed;
		};

	public:

		Event(int index, Vector2D pos)
			:
			index(index),
			pos(pos),
			type(Stick)
		{}

		Event(float val)
			:
			index(-1),
			val(val),
			type(Axis)
		{}

		Event(int index, bool pressed)
			:
			index(index),
			pressed(pressed),
			type(Button)
		{}

		Event()
			:
			index(-1),
			pressed(false),
			type(Invalid)
		{}

		float getAxisValue() const
		{
			assert(type == Axis);
			return val;
		}

		int getIndex() const
		{
			assert(type == Button || type == Stick);
			return index;
		}

		bool isPressed() const
		{
			assert(type == Button);
			return pressed;
		}

		Vector2D getStickPosition() const 
		{
			assert(type == Stick);
			return pos;
		}

		bool isValid() const
		{
			return(type != Invalid);
		}

		Type getType()const 
		{
			return type;
		}
	};

private:

	const unsigned int maxEvents = 64;
	DIJOYSTATE2 state;
	IDirectInputDevice8W* pDev = nullptr;
	std::queue<Event> events;
public:

	Gamepad(IDirectInput8W* pInput, HWND hWnd, const GUID& guid)
	{
		pInput->CreateDevice(guid, &pDev, nullptr);
		pDev->SetDataFormat(&c_dfDIJoystick2);
		{
			DIPROPDWORD prop;
			prop.diph.dwHeaderSize = sizeof(prop.diph);
			prop.diph.dwSize = sizeof(prop);
			prop.diph.dwHow = DIPH_DEVICE;
			prop.diph.dwObj = 0;
			prop.dwData = 256;

			pDev->SetProperty(DIPROP_BUFFERSIZE, &prop.diph);
		}
		pDev->EnumObjects((LPDIENUMDEVICEOBJECTSCALLBACKW)EnumObjectCallback, this, DIDFT_ALL);
		pDev->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_EXCLUSIVE);
	}

	~Gamepad() 
	{
		if(pDev != nullptr)
		{
			pDev->Unacquire();
			pDev->Release();
			pDev = nullptr;
		}
	}

	Vector2D getStickData(int index = 0)const 
	{
		assert(index >= Dpad && index <= Analog2);
		switch (index)
		{
		case Dpad:
			switch (state.rgdwPOV[0]) 
			{
			case 0:
				return{ 0.0f , -1000.0f };
			case 4500:
				return{ 1000.0f , -1000.0f };
			case 9000:
				return{ 1000.0f , 0.0f };
			case 13500:
				return{ 1000.0f, 1000.0f };
			case 18000:
				return{ 0.0f, 1000.0f };
			case 22500:
				return{ -1000.0f, 1000.0f };
			case 27000:
				return{ -1000.0f, 0.0f };
			case 31500:
				return{ -1000.0f, -1000.0f };
			default:
				return{ 0.0f, 0.0f };
			}
		case Analog1:
			return{ float(state.lX), float(state.lY) };
		case Analog2:
			return{ float(state.lRx), float(state.lRy) };
		default:
			return{ 0.0f, 0.0f };
		}
	}

	float getAxisData(int index)
	{
		if (index = 1)
			return(float(state.lZ));
		if (index = 2)
			return(float(state.lRz));
	}

	bool getButtonPressed(int index) 
	{
		assert(index >= 0 && index <= 127);
		return(state.rgbButtons[index] & 0x80) == 0x80;
	}

	void update()
	{
		pDev->Acquire();
		pDev->Poll();
		pDev->GetDeviceState(sizeof(state), &state);

		DWORD nItems = 20;
		std::array<DIDEVICEOBJECTDATA, 20> data;
		pDev->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), data.data(), &nItems, 0);
		for (unsigned int i = 0; i < nItems; i++)
		{
			if (data[i].dwOfs >= offsetof(DIJOYSTATE2, rgbButtons[0]) &&
				data[i].dwOfs <= offsetof(DIJOYSTATE2, rgbButtons[127]))
			{
				events.emplace(data[i].dwOfs - offsetof(DIJOYSTATE2, rgbButtons[0]),
					data[i].dwData && 0x80 == 0x80);
			}

			else if (data[i].dwOfs == offsetof(DIJOYSTATE2, rgdwPOV[0]))
			{
				Vector2D vec;

				switch (data[i].dwData)
				{
				case 0:
					vec = { 0.0f , -1000.0f };
				case 4500:
					vec = { 1000.0f , -1000.0f };
				case 9000:
					vec = { 1000.0f , 0.0f };
				case 13500:
					vec = { 1000.0f, 1000.0f };
				case 18000:
					vec = { 0.0f, 1000.0f };
				case 22500:
					vec = { -1000.0f, 1000.0f };
				case 27000:
					vec = { -1000.0f, 0.0f };
				case 31500:
					vec = { -1000.0f, -1000.0f };
				default:
					vec = { 0.0f, 0.0f };
				}
				events.emplace(Dpad, vec);
			}

			else if (data[i].dwOfs == offsetof(DIJOYSTATE2, lX) ||
				data[i].dwOfs == offsetof(DIJOYSTATE2, lY))
			{
				events.emplace(Analog1, Vector2D{ float(state.lX),float(state.lY) });
			}
			else if (data[i].dwOfs == offsetof(DIJOYSTATE2, lRx) ||
				data[i].dwOfs == offsetof(DIJOYSTATE2, lRy))
			{
				events.emplace(Analog2, Vector2D{ float(state.lRx),float(state.lRy) });
			}
			else if (data[i].dwOfs == offsetof(DIJOYSTATE2, lZ))
			{
				events.emplace(float(data[i].dwData));
			}
			else if (data[i].dwOfs == offsetof(DIJOYSTATE2, lRz))
			{
				events.emplace(float(data[i].dwData));
			}
			if (events.size() > maxEvents)
			{
				events.pop();
			}

		}
	}

	Event readEvent() 
	{
		Event e = events.front();
		events.pop;
		return e;
	}

	Event peekEvent()const 
	{
		return events.front();
	}

	bool isEmpty() 
	{
		return events.empty();
	}
private:
	static BOOL CALLBACK
		EnumObjectCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext) 
	{
		Gamepad* pPad = reinterpret_cast<Gamepad*>(pContext);
		if (pdidoi->dwType & DIDFT_AXIS)
		{
			DIPROPRANGE diprg;
			diprg.diph.dwSize = sizeof(DIPROPRANGE);
			diprg.diph.dwHeaderSize = sizeof(DIPROPRANGE);
			diprg.diph.dwHow = DIPH_BYID;
			diprg.diph.dwObj = pdidoi->dwType;

			diprg.lMin = -1000;
			diprg.lMax = +1000;

			pPad->pDev->SetProperty(DIPROP_RANGE, &diprg.diph);

			DIPROPDWORD didw;
			didw.diph.dwSize = sizeof(DIPROPDWORD);
			didw.diph.dwHeaderSize = sizeof(DIPROPDWORD);
			didw.diph.dwHow = DIPH_BYID;
			didw.diph.dwObj = pdidoi->dwType;
			didw.dwData = 100;

			pPad->pDev->SetProperty(DIPROP_DEADZONE, &didw.diph);
		}
		return DIENUM_CONTINUE;
	}

};

class DirectInput
{
public:
	DirectInput(HWND hWnd)
		:
		hWnd(hWnd)
	{
		DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&pInput, NULL);

		pInput->EnumDevices(DI8DEVCLASS_GAMECTRL,(LPDIENUMDEVICESCALLBACKW)DeviceEnumCallback,
			(VOID*)this, DIEDFL_ATTACHEDONLY);
	}
	~DirectInput()
	{
		if (pInput != nullptr)
		{
			pInput->Release();
			pInput = nullptr;
		}
	}
	Gamepad& GetPad()
	{
		return *pPad;
	}
private:
	static BOOL CALLBACK
		DeviceEnumCallback(const DIDEVICEINSTANCE* instance, VOID* context)
	{
		DirectInput* pInput = static_cast<DirectInput*>(context);
		pInput->pPad = std::make_unique<Gamepad>(pInput->pInput, pInput->hWnd, instance->guidInstance);
		return DIENUM_STOP;
	}
private:
	const HWND hWnd;
	std::unique_ptr<Gamepad> pPad;
	IDirectInput8W* pInput = nullptr;
};



#endif // !INPUT_DEVICE