package phais

import (
	"image/color"
	"log"
)

type initDataStruct struct {
	numPlayers int
	boardSize  int
}

type nameColorStruct struct {
	name     string
	r        int
	g        int
	b        int
	colorSet bool
}

type channelDataPair struct {
	channel chan bool
	data    interface{}
	err     error
	hasData bool
}

var initData channelDataPair
var nameColor channelDataPair
var turnData channelDataPair
var moveData channelDataPair

const (
	MoveUp = iota
	MoveRight
	MoveDown
	MoveLeft
)

type EnemyTurn struct {
	PlayerID int
	X        int
	Y        int
}

type Turn struct {
	GameOver   string
	X          int
	Y          int
	EnemyTurns []EnemyTurn
}

func init() {
	initData.channel = make(chan bool)
	nameColor.channel = make(chan bool)
	turnData.channel = make(chan bool)
	moveData.channel = make(chan bool)
}

func (c *channelDataPair) waitForData() {
	if !c.hasData {
		<-c.channel
	}
}

func (c *channelDataPair) announceData() {
	c.hasData = true
	go func() { c.channel <- true }()
}

func GetBoardSize() int {
	if !nameColor.hasData {
		log.Fatal("Attempt to request for board size before setting name and color")
	}

	initData.waitForData()

	if initData.err != nil {
		log.Fatal("Network error while retrieving initial data: ",
			initData.err)
	}

	initDataData := initData.data.(initDataStruct)
	return initDataData.boardSize
}

func GetNumPlayers() int {
	if !nameColor.hasData {
		log.Fatal("Attempt to request for number of players before setting name and color")
	}

	initData.waitForData()

	if initData.err != nil {
		log.Fatal("Network error while retrieving initial data: ",
			initData.err)
	}

	initDataData := initData.data.(initDataStruct)
	return initDataData.numPlayers
}

func WaitForTurn() Turn {
	if currentState == StateDisconnected {
		log.Fatal("Attempt to wait for turn while not connected to server")
	}

	turnData.waitForData()

	if turnData.err != nil {
		log.Fatal("Network error while retrieving turn data (Is the game over?): ",
			turnData.err)
	}

	turnDataData := turnData.data.(Turn)
	turnData.data = Turn{}
	turnData.hasData = false

	return turnDataData
}

func MakeMove(move int) error {
	if currentState == StateDisconnected {
		return ErrDisconnected
	}

	if moveData.hasData {
		return ErrDataAlreadySet
	}

	if move != MoveUp && move != MoveRight && move != MoveDown &&
		move != MoveLeft {
		return ErrInvalidData
	}

	moveData.data = move
	moveData.announceData()

	return nil
}

func SetName(name string) error {
	if currentState == StateDisconnected {
		return ErrDisconnected
	}

	if nameColor.hasData {
		return ErrDataAlreadySet
	}

	if nameColor.data == nil {
		nameColor.data = nameColorStruct{}
	}

	nameColorData := nameColor.data.(nameColorStruct)
	nameColorData.name = name

	nameColor.data = nameColorData

	if nameColorData.colorSet {
		nameColor.announceData()
	}

	return nil
}

func SetColor(thisColor color.Color) error {
	if currentState == StateDisconnected {
		return ErrDisconnected
	}

	if nameColor.hasData {
		return ErrDataAlreadySet
	}

	if nameColor.data == nil {
		nameColor.data = nameColorStruct{}
	}

	rawR, rawG, rawB, _ := thisColor.RGBA()

	nameColorData := nameColor.data.(nameColorStruct)
	nameColorData.r, nameColorData.g, nameColorData.b =
		int(rawR>>8), int(rawG>>8), int(rawB>>8)
	nameColorData.colorSet = true

	nameColor.data = nameColorData

	if nameColorData.name != "" {
		nameColor.announceData()
	}

	return nil
}

var cells [500][500]bool

func IsCellElectrified(x int, y int) bool {
	return cells[x][y]
}

func setElectrified(x int, y int) {
	cells[x][y] = true
}
