package phais

import (
	"log"
	"strconv"
	"time"
)

func handleName(commands []string) {
	if !nameColor.hasData {
		<-nameColor.channel
	}

	if nameColor.hasData {
		nameColorData := nameColor.data.(nameColorStruct)
		err := tellServer("NAME " + nameColorData.name + " " +
			strconv.Itoa(nameColorData.r) + " " +
			strconv.Itoa(nameColorData.g) + " " +
			strconv.Itoa(nameColorData.b))
		if err != nil {
			log.Fatal("Network error while telling server name")
		}

		return
	} else {
		log.Fatal("Did not receive name color information")
	}
}

func handleNewGame(commands []string) {
	numPlayers, err := strconv.Atoi(commands[1])
	if err != nil {
		initData.err = err
		initData.announceData()
		return
	}

	boardSize, err := strconv.Atoi(commands[2])
	if err != nil {
		initData.err = err
		initData.announceData()
		return
	}

	responseKey, err := strconv.Atoi(commands[3])
	if err != nil {
		initData.err = err
		initData.announceData()
	}

	initDataData := initDataStruct{
		numPlayers: numPlayers,
		boardSize:  boardSize,
	}

	initData.data = initDataData

	initData.announceData()

	tellServer("READY " + strconv.Itoa(responseKey))
}

func handleLocation(commands []string) {
	for turnData.hasData {
		// Hurry up you slow poke!
		time.Sleep(time.Millisecond * 100)
	}

	playerID, err := strconv.Atoi(commands[1])
	if err != nil {
		turnData.err = err
		turnData.announceData()
		return
	}

	x, err := strconv.Atoi(commands[2])
	if err != nil {
		turnData.err = err
		turnData.announceData()
		return
	}

	y, err := strconv.Atoi(commands[3])
	if err != nil {
		turnData.err = err
		turnData.announceData()
		return
	}

	setElectrified(x, y)

	if turnData.data == nil {
		turnData.data = Turn{}
	}

	turnDataData := turnData.data.(Turn)

	if playerID == 0 {
		turnDataData.X, turnDataData.Y = x, y
	} else {
		turnDataData.EnemyTurns = append(turnDataData.EnemyTurns,
			EnemyTurn{
				PlayerID: playerID,
				X:        x,
				Y:        y,
			})
	}

	turnData.data = turnDataData
}

func handleYourMove(commands []string) {
	moveData.hasData = false
	moveData.data = 0
	turnData.announceData()

	moveData.waitForData()
	thisMove := moveData.data.(int)
	var dx, dy int

	switch thisMove {
	case MoveUp:
		dx = 0
		dy = -1
	case MoveDown:
		dx = 0
		dy = 1
	case MoveLeft:
		dx = -1
		dy = 0
	case MoveRight:
		dx = 1
		dy = 0
	}

	tellServer("MOVE " + strconv.Itoa(dx) + " " + strconv.Itoa(dy))
}

func handleGameOver(commands []string) {
	for i := 0; i < 500; i++ {
		for j := 0; j < 500; j++ {
			cells[i][j] = false
		}
	}

	var message string
	for i, str := range commands {
		if i == 0 {
			continue
		}
		message = message + str + " "
	}

	turnDataData := turnData.data.(Turn)
	turnDataData.GameOver = message[:len(message)-1]
	turnData.data = turnDataData
	turnData.announceData()
}

func handleError(commands []string) {
	var message string
	for i, str := range commands {
		if i == 0 {
			continue
		}
		message = message + str + " "
	}

	log.Println("phais: received error from server:", message)
}
