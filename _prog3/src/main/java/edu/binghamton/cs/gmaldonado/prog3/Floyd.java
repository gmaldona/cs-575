package edu.binghamton.cs.gmaldonado.prog3;

/*
 * CS 575 - Programming Assignment 3
 * Floyd-Warshall algorithm using dynamic programming approach.
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

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Floyd {

    /**
     * The list of {@link Problem}s to solve from the graph-input file
     */
    private final List<Problem> problems;

    /**
     * Common Interface between Problem and Solution. Needed this to abstract some of the labelling between IO
     */
    public static abstract class Couplet {

        private int id;
        private int n;

        public int getId() {
            return id;
        }

        public Couplet setId(final int id) {
            this.id = id;
            return this;
        }

        public Couplet setN(final int n) {
            this.n = n;
            return this;
        }

        public int getN() {
            return n;
        }
    }

    /**
     * Wrapper class to encapsulate what a problem looks like.
     */
    public static class Problem extends Couplet {

        private int[][] graph;

        public int[][] getGraph() {
            return graph;
        }

        public Problem initializeGraph(final int n) {
            graph = new int[n][n];
            return this;
        }
    }

    /**
     * Wrapper class to encapsulate what a solution looks like.
     */
    public static class Solution extends Couplet {

        private Problem problem;
        private int[][] distances;
        private int[][] pointers;

        public Solution setProblem(Problem problem) {
            this.problem = problem;
            return this;
        }

        public Solution setDistances(final int[][] distances) {
            this.distances = distances;
            return this;
        }

        public Solution setPointers(final int[][] pointers) {
            this.pointers = pointers;
            return this;
        }

        public Problem getProblem() {
            return problem;
        }

        public int[][] getDistances() {
            return distances;
        }

        public int[][] getPointers() {
            return pointers;
        }
    }

    /**
     *
     * @param problems a {@link List} of {@link Problem} to solve
     */
    public Floyd(List<Problem> problems) {
        this.problems = problems;
    }

    /**
     *
     * @return a {@link List} of {@link Solution} that were solved. One solution per {@link Problem}.
     */
    public List<Solution> computeShortestPaths() {

        /* DS to hold the problem solutions so the writer can iterator over each solution and write to disk */
        List<Solution> solutions = new ArrayList<>();

        for (Problem problem : problems) {
            int vertices = problem.getN();
            int[][] pointers  = new int[vertices][vertices];
            int[][] distances = new int[vertices][vertices];

            // Initialization of distance and pointer matrices.
            // Distance matrix is initialized to the weights of the input graph
            // Pointer matrix is initialized to all zeros
            for (int row = 0; row < vertices; row++) {
                for (int col = 0; col < vertices; col++) {
                    distances[row][col] = problem.getGraph()[row][col];
                    pointers [row][col]  = 0;
                }
            }

            // The meat and potatoes of  FLoyd's Algorithm. Chapter 7: Dynamic Programming, Slide 47.
            for (int k = 0; k < vertices; k++) {
                for (int i = 0; i < vertices; i++) {
                    for (int j = 0; j < vertices; j++) {
                        if (distances[i][j] > distances[i][k] + distances[k][j]) {
                            distances[i][j] = distances[i][k] + distances[k][j];
                            pointers [i][j] = k + 1;
                        } else {
                            distances[i][j] = distances[i][j];
                        }
                    }
                }
            }

            solutions.add((Solution) new Solution()
                                .setDistances(distances)
                                .setPointers(pointers)
                                .setProblem(problem)
                                .setId(problem.getId())
                                .setN(problem.getN())
            );
        }
        return solutions;
    }

    /**
     * Format a matrix to be printable to stdin or to a file. Includes number padding so the cols are aligned.
     *
     * @param graph Matrix to be pretty printed
     * @return A pretty printed matrix
     */
    public static String prettyPrintGraph(final int[][] graph) {
        StringBuilder prettyPrint = new StringBuilder();

        for (int i = 0; i < graph.length; i++) {
            for (int j = 0; j < graph[i].length; j++) {
                StringBuilder padding = new StringBuilder();
                padding.append(" ".repeat(Math.max(0, 3 - Integer.toString(graph[i][j]).length()))); // padding to align cols
                prettyPrint.append(padding).append(graph[i][j]).append("\t");
            }   prettyPrint.append("\n"); // hiding new scope
        }
        return prettyPrint.toString();
    }

    /**
     * FileWriter abstraction to write the expected output file to disk. Reads {@link Solution} and formats
     */
    protected static class FileWriter {

        /**
         * Interface to allow for an inner-function. This is useful for debug and commenting in and out
         * writing the intermediate paths from the output file.
         */
        public interface IntermediatePathWriter {
            void writeIntermediatePath() throws IOException;
        }

        /**
         * Prints intermediate vertices between some Vx and Vy to the outputPath.
         * Recursive.
         *
         * @param distances solution distance matrix
         * @param pointers solution pointer matrix
         * @param q index in a solution matrix
         * @param r index in a solution matrix
         * @param outputPath path to output file
         * @return the total distance to traverse path
         */
        public static int intermediatePath(final int[][] distances,
                                           final int[][] pointers,
                                           final int q, final int r,
                                           final Path outputPath) throws IOException {
            int totalDistance = 0;
            if (pointers[q][r] != 0) {
                totalDistance += intermediatePath(distances, pointers, q, pointers[q][r] - 1, outputPath);
                Files.write(outputPath, ("V" + pointers[q][r] + " ").getBytes(), StandardOpenOption.APPEND);
                totalDistance += intermediatePath(distances, pointers, pointers[q][r] - 1, r, outputPath);
            } else {
                totalDistance += distances[q][r];
            }
            return totalDistance;
        }

        /**
         * Writes each {@link Solution} results in the output.txt nicely formatted.
         *
         * @param solutions a {@link List} of {@link Solution}s
         * @param outputPath The path to the output.txt
         */
        public static void writeSolutionToFile(final List<Solution> solutions, final Path outputPath) throws IOException {

            File outputFile = outputPath.toFile();
            if (! outputFile.exists()) {
                outputFile.createNewFile();
            } else {
                Files.write(outputPath, "".getBytes(), StandardOpenOption.TRUNCATE_EXISTING);
            }

            for (Solution solution : solutions) {
                // A stream of file writing operations. Messy but look at the file output if you want to see the output
                String label = "Problem " + solution.getId() + ": n = " + solution.getN() + "\n";
                Files.write(outputPath, label.getBytes(), StandardOpenOption.APPEND);
                Files.write(outputPath, "P matrix:\n".getBytes(), StandardOpenOption.APPEND);
                Files.write(outputPath, prettyPrintGraph(solution.pointers).getBytes(), StandardOpenOption.APPEND);

                new IntermediatePathWriter() {
                    @Override
                    public void writeIntermediatePath() throws IOException {
                        // Getting the output file in the right format. Might look messy but look at the file output if you want to see
                        int[][] graph = solution.getProblem().getGraph();
                        for (int i = 1; i <= graph.length; i++) {
                            Files.write(outputPath, ("\nV" + i + "-Vj: shortest path and length\n").getBytes(), StandardOpenOption.APPEND);

                            for (int j = 1; j <= graph.length; j++) {
                                Files.write(outputPath, ("V" + i + " ").getBytes(), StandardOpenOption.APPEND);
                                int distance = intermediatePath(solution.getDistances(), solution.getPointers(), i - 1, j - 1, outputPath);
                                Files.write(outputPath, ("V" + j + " ").getBytes(), StandardOpenOption.APPEND);
                                Files.write(outputPath, (": " + distance).getBytes(), StandardOpenOption.APPEND);
                                Files.write(outputPath, "\n".getBytes(), StandardOpenOption.APPEND);
                            }
                        }
                    }
                }.writeIntermediatePath();
            }
        }
    }

    /**
     * FileReader abstraction to read the graph-file, parse the Problem into a {@link Problem} and the necessary
     * information needed to perform the computation.
     */
    public static class FileReader {

        /**
         * Takes in a file and generates {@link Problem} for each problem listed
         * @param file graph-file that contains a list of problems
         */
        public static List<Problem> generateProblemsFromFile(final File file) throws IOException {
            BufferedReader reader = new BufferedReader(new java.io.FileReader(file));
            // regex to find the "Problem" label along with the Problem ID and Number of Vertices
            Pattern PROBLEM_PATTERN = Pattern.compile("Problem\\s+([0-9]+):\\s*n\\s*=\\s*([0-9]+)");
            // regex to find the weights of the graph from the graph-file
            Pattern WEIGHTS_PATTERN = Pattern.compile("-?[0-9]+");

            String line;
            List<Problem> problems = new ArrayList<>();
            Problem problem = null;

            int i = 0; // setting up matrix indices
            int j = 0; // setting up matrix indices
            while ((line = reader.readLine()) != null) {

                if (line.isEmpty()) { // empty line is a line break to the next problem.
                    i = 0;
                    continue;
                }  else if (line.startsWith("Problem")) {
                    // I don't trust that the whitespaces will match. One hardcoded number of spaces and things will
                    // start throwing... Going with a regex.
                    Matcher matcher = PROBLEM_PATTERN.matcher(line);
                    if (matcher.find()) {
                        problem = (Problem) new Problem()
                                .setId(Integer.parseInt(matcher.group(1)))
                                .setN(Integer.parseInt(matcher.group(2)));

                        problems.add(
                                problem.initializeGraph(problem.getN()) // inline to set up and add to problems list
                        );
                    } else {
                        System.err.println("Formatting issue in the file. Please check the format.");
                        System.exit(1);
                    }
                } else {
                    // Only possibility if there's a format issue which is caught above
                    if (problem == null) { continue; }

                    Matcher matcher = WEIGHTS_PATTERN.matcher(line);
                    while (matcher.find()) {
                        problem.getGraph()[i][j] = Integer.parseInt(matcher.group());
                        j++;
                    } i++;
                } j = 0;
            }
            return problems;
        }
    }

    public static void main(String[] args) throws IOException {
        if (args.length != 1) {
            System.err.println("Usage: java floyd <file>");
            System.exit(1);
        }

        System.err.println("[FINE] Loading input file: " + args[0]);

        final File inputFile  = new File(args[0]);
        final Path outputPath = inputFile.toPath().getParent().resolve("output.txt");

        List<Problem> problems = FileReader.generateProblemsFromFile(inputFile);

        List<Solution> solutions = new Floyd(problems)
                .computeShortestPaths();

        FileWriter.writeSolutionToFile(solutions, outputPath);

        System.err.println("[FINE] Generating output file: " + outputPath);
    }
}
