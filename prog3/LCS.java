import java.util.Arrays;

/*
 * CS 575 - Programming Assignment 3
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

/* 10% of the grade will be based on good coding style and meaningful comments. */
/* A little subjective... but okay */

/**
 * High level recurrence equation for the computation of LCS using Dynamic Programming
 *
 * lenLCS(i, j) =
 *      - 0                                         if i == 0  || j == 0
 *      - lenLCS(i - 1, j - 1) + 1                  if i,j > 0 && x[i] = y[j]
 *      - max{lenLCS(i - 1, j), lenLCS(i, j - 1)}   otherwise
 *
 */
class LCS {

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
        private int value;
        private Direction direction;

        /**
         *
         * @param value integer value of a table entry
         * @param direction direction value of a table entry
         */
        public LCSValue(int value, LCS.Direction direction) {
            this.value = value;
            this.direction = direction;
        }

        public void setValue(Integer value) {
            this.value = value;
        }

        public void setDirection(Direction direction) {
            this.direction = direction;
        }

        public int getValue() {
            return value;
        }

        public Direction getDirection() {
            return direction;
        }
    }

    /**
     * Initialization of the lenLCS array of zeros and NULL directions.
     *
     * @param lenLCS Empty LCS table
     * @param domain Domain String (stand-in for S1)
     * @param target Target String (stand-in for S2)
     */
    public static void lcsPreconditions(LCSValue[][] lenLCS, String domain, String target) {
        Arrays.stream(lenLCS).forEach(row -> Arrays.fill(row, new LCSValue(-1, Direction.NULL)));

        for (int col = 0; col < lenLCS.length; col++) {
            lenLCS[0][col] = new LCSValue(0, Direction.NULL);
        }

        for (int row = 0; row < lenLCS.length; row++) {
            lenLCS[row][0] = new LCSValue(0, Direction.NULL);
        }
    }

    /**
     * Used for debugging. Should not appear in the final output.
     * @param lenLCS LCS table
     */
    public static void displayLenLCS(LCSValue[][] lenLCS) {
        // display 2d grid of len-lcs.
        System.out.print("\n");

        for (int i = 0; i < lenLCS.length; i++) {
            for (int j = 0; j < lenLCS[i].length; j++) {
                StringBuilder padding = new StringBuilder();

                padding.append(" ".repeat(Math.max(0, 5 - Integer.toString(lenLCS[i][j].getValue()).length())));

                System.out.print(padding.toString() + lenLCS[i][j].getValue() + "(" + lenLCS[i][j].getDirection().getCode() + ")\t");
            }
            System.out.println(); // hiding scope to clean up method
        }
    }

    /**
     * @param domain
     * @param target
     */
    public static void compute(String domain, String target) {
        LCSValue[][] lenLCS = new LCSValue[target.length() + 1][target.length() + 1];
        lcsPreconditions(lenLCS, domain, target); // array initialization

        for (int i = 1; i <= domain.length(); i++) {
            for (int j = 1; j <= target.length(); j++) {

                if (domain.charAt(i - 1) == target.charAt(j - 1)) {
                    lenLCS[i][j] = new LCSValue(1 + lenLCS[i - 1][j - 1].getValue(), Direction.DGNL);
                } else {
                    // otherwise condition on the recurrence equation. Weird Java doesn't have a quick max
                    // function... or maybe I'm dumb... IDK.
                    if (lenLCS[i - 1][j].getValue() >= lenLCS[i][j - 1].getValue()) {
                        lenLCS[i][j] = new LCSValue(lenLCS[i - 1][j].getValue(), Direction.__UP);
                    } else {
                        lenLCS[i][j] = new LCSValue(lenLCS[i][j - 1].getValue(), Direction.LEFT);
                    }
                }
            }
        }

        int largestSequenceCount = 0;
        int x = 0;
        int y = 0;
        for (int i = lenLCS.length - 1; i >= 0; i--) {
            for (int j = lenLCS[i].length - 1; j >= 0; j--) {
                if (largestSequenceCount < lenLCS[i][j].getValue() && lenLCS[i][j].getDirection() == Direction.DGNL) {
                    largestSequenceCount = lenLCS[i][j].getValue();
                    x = i;
                    y = j;
                }
            }
        }

        StringBuilder largestSequenceString = new StringBuilder();
        LCSValue entry = lenLCS[x][y];
        while (entry.getDirection() != Direction.NULL) {
            // Switch based on the direction from the computation.
            // Follow the direction until you get to a Direction.NULL
            switch (entry.getDirection()) {
                case LEFT -> {
                    entry = lenLCS[x][y - 1];
                     y    = y - 1;
                }
                case __UP -> {
                    entry = lenLCS[x - 1][y];
                    x     = x - 1;
                }
                // If diagonal, there is a subsequence.
                case DGNL -> {
                    largestSequenceString.insert(0, target.charAt(y - 1));
                    entry = lenLCS[x - 1][y - 1];
                    x     = x - 1;
                    y     = y - 1;
                }
            }
        }

        System.out.println("Length of LCS: " +   largestSequenceCount);
        System.out.println("LCS: " +   largestSequenceString);
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java lcs <input-string1> <input-string2>");
            System.exit(1);
        }

        String domain = args[0]; // Used as a stand-in for S1 (cols)
        String target = args[1]; // Used as a stand-in for S2 (rows)

        // padding BS...
        int larger = 0;
        int smaller = 0;
        StringBuilder padding = new StringBuilder();
        if (domain.length() > target.length()) {
            larger  = domain.length();
            smaller = target.length();
        } else if (domain.length() < target.length()) {
            larger  = target.length();
            smaller = domain.length();
        }
        padding.append(" ".repeat(larger - smaller));

        if (domain.length() < target.length()) {
            domain = domain + padding;
        } else {
            target = target + padding;
        }

        compute(domain, target);
    }
}
