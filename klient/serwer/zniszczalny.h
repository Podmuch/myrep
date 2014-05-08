#pragma once

#include "obiekt.h"

class Zniszczalny : public Obiekt
{
	private:
		int zycie;
	public:
		Zniszczalny(int x1, int x2, int y1, int y2, int zycie) : Obiekt(x1,x2,y1,y2)
		{
			this->zycie = zycie;
		}
		int getZycie() { return zycie; }
		void setZycie(int zycie) { this->zycie = zycie; }
		bool czyZniszczono() { return (zycie > 0 ? false : true); }
};