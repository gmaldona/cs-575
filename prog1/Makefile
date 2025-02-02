# CS 575 - Programming Assignment 1
#
# Graduate student @ School of Computing, Binghamton University.
#
# author: Gregory Maldonado
# email : gmaldonado@cs.binghamton.edu
# date  : 2025-01-30
# web   : https://cs.binghamton.edu/~gmaldonado/
# file name:   baseball_cards.cc
#
# THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

CC     = g++
CFLAGS = -std=c++17 # -Wall -Wextra -pedantic -g -O3
TARGET = baseball_cards
OUT    = program1

.PHONY: default
default : $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(OUT) $(TARGET).o
	$(RM) *.o

$(TARGET).o: $(TARGET).cc $(TARGET).h
	$(CC) $(CFLAGS) -c $(TARGET).cc