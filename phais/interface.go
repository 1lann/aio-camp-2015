package phais

import (
	"image/color"
)

type initDataStruct struct {
	numPlayers int
	boardSize  int
	playerID   int
}

type channelDataPair struct {
	channel chan interface{}
	data    interface{}
	hasData bool
}

var initData channelDataPair
var register channelDataPair

func GetBoardSize() int {

}

func GetPlayerID() int {

}

func GetNumPlayers() int {

}

func GetStartingPosition() Position {

}

func SetName(string name) {

}

func SetColor(thisColor color.Color) {

}

func WaitNextEvent() Event {

}
