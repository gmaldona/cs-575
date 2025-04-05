package edu.binghamton.cs.gmaldonado.prog3;

/*
 * CS 575 - Programming Assignment 2
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

    private final List<Problem> problems;

    /**
     * Common Interface between Problem and Solution. Needed this to abstract some of the labelling between IO
     */
    public static abstract class Couplet {

        private Integer id;
        private Integer n;

        public Integer getId() {
            return id;
        }

        public Couplet setId(final Integer id) {
            this.id = id;
            return this;
        }

        public Couplet setN(final Integer n) {
            this.n = n;
            return this;
        }

        public Integer getN() {
            return n;
        }
    }

    /**
     * Wrapper class to encapsulate what a problem looks like.
     */
    public static class Problem extends Couplet {

        private Integer[][] graph;

        public Integer[][] getGraph() {
            return graph;
        }

        public Problem initializeGraph(final Integer n) {
            graph = new Integer[n][n];
            return this;
        }
    }

    public static class Solution extends Couplet {

        private Integer[][] distances;
        private Integer[][] pointers;

        public Solution setDistances(final Integer[][] distances) {
            this.distances = distances;
            return this;
        }

        public Solution setPointers(final Integer[][] pointers) {
            this.pointers = pointers;
            return this;
        }

        public Integer[][] getDistances() {
            return distances;
        }

        public Integer[][] getPointers() {
            return pointers;
        }
    }

    /**
     *
     * @param problems
     */
    public Floyd(List<Problem> problems) {
        this.problems = problems;
    }

    public List<Solution> computeShortestPaths() {

        /* DS to hold the problem solutions so the writer can iterator over each solution and write to disk */
        List<Solution> solutions = new ArrayList<>();

        for (Problem problem : problems) {

            Integer vertices = problem.getN();
            Integer[][] pointers = new Integer[vertices][vertices];
            Integer[][] distances = new Integer[vertices][vertices];

            // Shallow copy. Even though they are just integers, I did use "Integer" so just in case.
            for (int row = 0; row < vertices; row++) {
                for (int col = 0; col < vertices; col++) {
                    distances[row][col] = problem.getGraph()[row][col];
                    pointers[row][col]  = 0;
                }
            }

            // The meat and potatoes of  FLoyd's Algorithm. Chapter 7: Dynamic Programming, Slide 47.
            for (int k = 0; k < vertices; k++) {
                for (int i = 0; i < vertices; i++) {
                    for (int j = 0; j < vertices; j++) {
                        if (distances[i][j] > distances[i][k] + distances[k][i]) {
                            distances[i][j] = distances[i][k] + distances[k][j];
                            pointers[i][j] = k;
                        }
                    }
                }
            }

            solutions.add((Solution) new Solution()
                                .setDistances(distances)
                                .setPointers(pointers)
                                .setId(problem.getId())
                                .setN(problem.getN())
            );

//            System.out.println(prettyPrintGraph(pointers));
        }

        return solutions;
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

        System.err.println("[FINE] Generating output file: " + outputPath);
    }

    /**
     *
     * @param graph
     */
    public static String prettyPrintGraph(final Integer[][] graph) {
        String prettyPrint = "";

        for (int i = 0; i < graph.length; i++) {
            for (int j = 0; j < graph[i].length; j++) {
                StringBuilder padding = new StringBuilder();

                padding.append(" ".repeat(Math.max(0, 3 - Integer.toString(graph[i][j]).length())));

                prettyPrint = prettyPrint +  padding.toString() + (graph[i][j] != null ? graph[i][j] : "_") + "\t";
            }   prettyPrint = prettyPrint + "\n"; // hiding new scope
        }
        return prettyPrint;
    }

    /**
     * FileWriter abstraction to write the expected output file to disk. Reads {@link Solution} and formats
     */
    protected static class FileWriter {

        /**
         *
         * @param solutions
         * @param outputPath
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

                Files.write(outputPath, "\n".getBytes(), StandardOpenOption.APPEND);
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
            Pattern WEIGHTS_PATTERN = Pattern.compile("[0-9]+");

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
}
