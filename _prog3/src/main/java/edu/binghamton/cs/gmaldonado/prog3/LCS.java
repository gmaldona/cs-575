package edu.binghamton.cs.gmaldonado.prog3;

import java.util.Arrays;

/*
 * CS 575 - Programming Assignment 2
 * Longest Common Subsequence (LCS) algorithm using dynamic programming approach.
 *
 * Graduate student @ School of Computing, Binghamton University.
 *
 * author: Gregory Maldonado
 * email : gmaldonado@cs.binghamton.edu
 * date  : 2025-04-04
 * web   : https://cs.binghamton.edu/~gmaldonado
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

public class LCS {

    enum Direction {
        __UP("U"), // up        direction
        LEFT("L"), // left      direction
        DGNL("D"), // diagonal  direction
        NULL("_"); // no (null) direction

        final String code;

        /**
         * @param code Stand-in code for directionality. Easier to print in the display method.
         */
        Direction(String code) {
            this.code = code;
        }

        public String getCode() {
            return code;
        }
    }

    /**
     * Wrapper class for a value stored within the table.
     * A table entry contains the Integer value + the direction of element that was used in the computation.
     */
    public static class LCSValue {
        Integer value;
        Direction direction;

        /**
         *
         * @param value
         * @param direction
         */
        public LCSValue(Integer value, LCS.Direction direction) {
            this.value = value;
            this.direction = direction;
        }
    }

    /**
     * Initialization of the lenLCS array of zeros and NULL directions.
     *
     * @param lenLCS
     * @param domain
     * @param target
     */
    public static void lcsPreconditions(LCSValue[][] lenLCS, String domain, String target) {
        Arrays.stream(lenLCS).forEach(row -> Arrays.fill(row, new LCSValue(-1, Direction.NULL)));

        for (int col = 0; col < lenLCS.length; col++) {
            lenLCS[0][col] = new LCSValue(0, Direction.NULL);
        }

        for (int row = 0; row < lenLCS.length; row++) {
            lenLCS[row][0] = new LCSValue(0, Direction.NULL);
        }

         displayLenLCS(lenLCS, domain, target);
    }

    /**
     *
     * @param lenLCS
     * @param domain
     * @param target
     */
    public static void displayLenLCS(LCSValue[][] lenLCS, String domain, String target) {
        // display 2d grid of len-lcs. TODO: Add some string padding to make it pretty and easy to read.
        for (LCSValue[] row : lenLCS) {
            for (LCSValue col : row) {
                System.out.print(col.value + "\t");
            }
            System.out.println();
        }
    }

    /**
     *
     * @param lenLCS
     * @param domain
     * @param target
     */
    public static void compute(LCSValue[][] lenLCS, String domain, String target) {
        lcsPreconditions(lenLCS, domain, target); // array initialization
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java lcs <input-string1> <input-string2>");
            System.exit(1);
        }

        String domain = args[0]; // Used as a stand-in for S1 (cols)
        String target = args[1]; // Used as a stand-in for S2 (rows)

        System.out.println("domain: " + domain);
        System.out.println("target: " + target);
        System.out.println();

        LCSValue[][] lenLCS = new LCSValue[domain.length()][target.length()];
        compute(lenLCS, domain, target);
    }
}
