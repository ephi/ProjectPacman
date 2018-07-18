#pragma once
enum DIRECTION {Left,Right,Up,Down};
class MovmentVec /*: public CObject*/
{
public:
	
	//DECLARE_SERIAL(MovmentVec)
	MovmentVec();
	MovmentVec(int speed,DIRECTION direction);
	~MovmentVec(void);
	int getSpeed() const;
	DIRECTION getDirection() const;
	void setSpeed(int speed);
	void setDirection(DIRECTION direction);
	void Serialize(CArchive& archive);
private:
	int speed;
	DIRECTION direction;
};

//CArchive& operator>>(CArchive& in, MovmentVec::DIRECTION& direction)
//{
//	unsigned u = 0;
//	in << u;
//	direction = static_cast<MovmentVec::DIRECTION>(u);
//	return in;
//}
//
//CArchive& operator<<(CArchive& out, MovmentVec::DIRECTION& direction)
//{
//	unsigned u = 0;
//	out << u;
//	direction = static_cast<MovmentVec::DIRECTION>(u);
//	return out;
//}



