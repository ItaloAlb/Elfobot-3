#pragma once

class Pokemon
{
	private:
		int next_attack_time;
		

	public:

		Pokemon(char pokemon[]);

		Pokemon();

		~Pokemon();

		void Attack();

		bool Can_Attack();
};

