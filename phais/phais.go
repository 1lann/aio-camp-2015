package phais

import (
	"net"
	"strconv"
)

var serverConnection net.Conn

type Position struct {
	X int
	Y int
}

type Event struct {
}

func tellServer(string data) error {
	return serverConnection.Write([]byte(data))
}

func Connect(address string, port int) error {
	serverConnection, err = net.Dial("tcp", address+":"+strconv.Itoa(port))
	if err != nil {
		return err
	}

}
