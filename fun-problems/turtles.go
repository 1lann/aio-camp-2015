package main

import (
	"bufio"
	"fmt"
	"os"
)

type cell struct {
	system int
	seq    int
	filled bool
}

type coord struct {
	x int
	y int
}

var field [][]cell
var systemConnection map[int]map[int][]coord
var width, height int

func main() {
	reader := bufio.NewReader(os.Stdin)
	fmt.Fscanf(reader, "%d %d", &height, &width)
	reader.ReadByte()

	field = make([][]cell, height)
	for row := 0; row < height; row++ {
		field[row] = make([]cell, width)
		for col := 0; col < width; col++ {
			thisCell, _ := reader.ReadByte()
			if thisCell == '.' {
				field[row][col] = cell{filled: false}
			} else {
				field[row][col] = cell{filled: true}
			}
		}
	}

	buildPathFinder()

	var numQueries int
	fmt.Fscanf(reader, "%d", &numQueries)
	for i := 0; i < numQueries; i++ {
		var startX, startY, endX, endY int
		fmt.Fscanf(reader, "%d %d %d %d", &startX, &startY, &endX, &endY)
		if canTravelTo(startX-1, startY-1, endX-1, endY-1) {
			fmt.Println("Yes")
		} else {
			fmt.Println("No")
		}
	}
}

func buildPathFinder() {
	systemConnection = make(map[int]map[int][]coord)
	var currentSystem = 1
	var seq = 1
	var found = false
	var startX, startY int

	for {
		found = false

		for startY = 0; startY < height; startY++ {
			for startX = 0; startX < width; startX++ {
				if !field[startY][startX].filled && field[startY][startX].system == 0 {
					found = true
					break
				}
			}
		}

		if !found {
			return
		}

		for y := startY; y < height; y++ {
			var modified = false

			for x := startX; x < width; x++ {
				if field[y][x].filled {
					if y <= 0 || field[y-1][x].system != currentSystem {
						break
					}
					continue
				}

				if y == 0 || field[y-1][x].system == currentSystem ||
					x == 0 || field[y][x-1].system == currentSystem {

					if field[y][x].system != 0 {
						// We're treading on someone else's land!
						if _, exists := systemConnection[currentSystem]; !exists {
							systemConnection[currentSystem] = make(map[int][]coord)
						}

						systemConnection[currentSystem][field[y][x].system] = append(
							systemConnection[currentSystem][field[y][x].system], coord{
								x: x,
								y: y - 1,
							})
						continue
					}

					field[y][x].system = currentSystem
					field[y][x].seq = seq
					seq++
					modified = true
				}

			}

			if !modified {
				break
			}
		}

		currentSystem++
		seq = 1
	}
}

func canTravelTo(startX int, startY int, endX int, endY int) bool {
	// Sanity check
	if startX > endX || startY > endY {
		return false
	}

	if field[startX][startY].system == field[endX][endY].system {
		return true
	}

	if 
	systemConnection[startX][startY]
}
