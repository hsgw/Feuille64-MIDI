# seeds.txt format
# test: output row col row_scale col_scale pitch_mode key filter_mode

class TestPattern:
    def __init__(self, line):
        temp = line.split()
        self.output = temp[1]
        self.row = temp[2]
        self.col = temp[3]
        self.rowScale = temp[4]
        self.colScale = temp[5]
        self.pitchMode = temp[6]
        self.key = temp[7]
        self.filterMode = temp[8]
    

inputPath = 'seeds.txt'
outputPath = 'tests.txt'

with open(inputPath) as f:
    with open(outputPath, "w") as o:
        lineCount = 1
        currentName = 0
        for line in f:
            if line[0] == '#':
                 currentName = line[2:].replace('\n', '')
            else:
                pattern = TestPattern(line)
                o.write("TEST(test_scale, {}_{}){{ EXPECT_EQ(scale_matrix_to_note_param({}, {}, {}, {}, {}, {}, {}), {}); }}\n"
                .format(currentName, lineCount, pattern.row, pattern.col, pattern.rowScale, pattern.colScale, pattern.pitchMode, pattern.key, pattern.filterMode, pattern.output))
                lineCount += 1
