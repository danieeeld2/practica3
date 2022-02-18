all: bin/Parchis

obj/main.o: src/main.cpp
	g++ -g -c src/main.cpp -o obj/main.o -I include/ -std=c++14

obj/ParchisGUI.o: src/ParchisGUI.cpp
	g++ -g -c src/ParchisGUI.cpp -o obj/ParchisGUI.o -I include/ -std=c++14

obj/Parchis.o: src/Parchis.cpp
	g++ -g -c src/Parchis.cpp -o obj/Parchis.o -I include/ -std=c++14

obj/Board.o: src/Board.cpp
	g++ -g -c src/Board.cpp -o obj/Board.o -I include/ -std=c++14

obj/Dice.o: src/Dice.cpp
	g++ -g -c src/Dice.cpp -o obj/Dice.o -I include/ -std=c++14

obj/ClickableSprite.o: src/ClickableSprite.cpp
	g++ -g -c src/ClickableSprite.cpp -o obj/ClickableSprite.o -I include/ -std=c++14

obj/DiceSprite.o: src/DiceSprite.cpp
	g++ -g -c src/DiceSprite.cpp -o obj/DiceSprite.o -I include/ -std=c++14

obj/PieceSprite.o: src/PieceSprite.cpp
	g++ -g -c src/PieceSprite.cpp -o obj/PieceSprite.o -I include/ -std=c++14

obj/SpriteAnimator.o: src/SpriteAnimator.cpp
	g++ -g -c src/SpriteAnimator.cpp -o obj/SpriteAnimator.o -I include/ -std=c++14

bin/Parchis: obj/main.o obj/ParchisGUI.o obj/Parchis.o obj/Board.o obj/Dice.o obj/DiceSprite.o obj/SpriteAnimator.o obj/PieceSprite.o obj/ClickableSprite.o
	g++ -g obj/main.o obj/ParchisGUI.o obj/Parchis.o obj/Board.o obj/Dice.o obj/DiceSprite.o obj/SpriteAnimator.o obj/PieceSprite.o obj/ClickableSprite.o -o bin/Parchis -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm -rf ./obj/*.o ./bin/*