#include "Seed.hpp"

void Seed::OnClickTemplt(FunctionName functionname)
{
	if (int result = m_world->GetSun() - m_price; result >= 0 && m_world->GetFunction() == FunctionName::None)
	{
		m_world->SetSun(result);
		m_world->AddObject(std::make_shared<CoolDown>(GetX(), GetY(), m_CoolTime, functionname,m_price ,m_world));
		m_world->SetFunction(functionname);
	}
}