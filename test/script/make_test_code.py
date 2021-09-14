#   Copyright 2021 Takuya Urakawa (hsgw)
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
