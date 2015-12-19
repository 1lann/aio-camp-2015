package phais

import (
	"bufio"
	"errors"
	"net"
	"strings"
)

type state int

const (
	StateDisconnected = iota
	StateConnected
)

var serverConnection net.Conn
var currentState state

var (
	ErrAlreadyConnected = errors.New("phais: client already connected")
	ErrDisconnected     = errors.New("phais: disconnected from server")
	ErrDataAlreadySet   = errors.New("phais: data already set")
	ErrInvalidData      = errors.New("phais: invalid data")
)

func tellServer(data string) error {
	if currentState == StateDisconnected {
		return ErrDisconnected
	}

	_, err := serverConnection.Write([]byte(data + "\t\n"))
	return err
}

func handleConnection() {
	defer serverConnection.Close()

	reader := bufio.NewReader(serverConnection)
	for {
		line, err := reader.ReadBytes('\n')
		if err != nil {
			currentState = StateDisconnected
			initData.err = err
			initData.announceData()
			turnData.err = err
			turnData.announceData()
			return
		}

		commands := strings.Split(string(line[:len(line)-1]), " ")

		switch commands[0] {
		case "NAME":
			handleName(commands)
		case "NEWGAME":
			handleNewGame(commands)
		case "YOURMOVE":
			handleYourMove(commands)
		case "GAMEOVER":
			handleGameOver(commands)
		case "LOCATION":
			handleLocation(commands)
		case "ERROR":
			handleError(commands)
		}
	}
}

func Connect(address string) error {
	if currentState != StateDisconnected {
		return ErrAlreadyConnected
	}

	currentState = StateConnected
	var err error
	serverConnection, err = net.Dial("tcp", address+":12317")
	if err != nil {
		return err
	}

	go handleConnection()

	return nil
}

func init() {
	currentState = StateDisconnected
}
