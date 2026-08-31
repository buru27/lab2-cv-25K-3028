#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;

class Image
{
    int nrows;
    int ncols;
    int **imageData;

public:

    // Default constructor
    Image()
    {
        nrows = 0;
        ncols = 0;
        imageData = 0;
    }

    // Parameterized constructor
    Image(int rows, int cols)
    {
        nrows = rows;
        ncols = cols;

        imageData = new int*[nrows];

        for(int i = 0; i < nrows; i++)
        {
            imageData[i] = new int[ncols];
        }
    }

    // Destructor
    ~Image()
    {
        if(imageData != 0)
        {
            for(int i = 0; i < nrows; i++)
            {
                delete [] imageData[i];
                imageData[i] = 0;
            }

            delete [] imageData;
            imageData = 0;
        }
    }

    // Fill image
    void fillImage()
    {
        for(int i = 0; i < nrows; i++)
        {
            for(int j = 0; j < ncols; j++)
            {
                cout << "Enter value: ";
                cin >> imageData[i][j];
            }
        }
    }

    // Display image
    void display()
    {
        for(int i = 0; i < nrows; i++)
        {
            for(int j = 0; j < ncols; j++)
            {
                cout << imageData[i][j] << " ";
            }

            cout << endl;
        }
    }

    // Operator () with boundary checking
    int &operator()(int row, int col)
    {
        if(row < 0 || row >= nrows ||
           col < 0 || col >= ncols)
        {
            cout << "Array Index Out of Bound" << endl;
            exit(1);
        }

        return imageData[row][col];
    }

    // Copy constructor
    Image(const Image &rhs)
    {
        nrows = rhs.nrows;
        ncols = rhs.ncols;

        imageData = new int*[nrows];

        for(int i = 0; i < nrows; i++)
        {
            imageData[i] = new int[ncols];

            memcpy(imageData[i],
                   rhs.imageData[i],
                   sizeof(int) * ncols);
        }
    }

    // Assignment operator
    Image &operator=(const Image &rhs)
    {
        if(this == &rhs)
        {
            return *this;
        }

        // Delete old memory
        for(int i = 0; i < nrows; i++)
        {
            delete [] imageData[i];
        }

        delete [] imageData;

        // Copy rows and columns
        nrows = rhs.nrows;
        ncols = rhs.ncols;

        // Allocate new memory
        imageData = new int*[nrows];

        for(int i = 0; i < nrows; i++)
        {
            imageData[i] = new int[ncols];

            memcpy(imageData[i],
                   rhs.imageData[i],
                   sizeof(int) * ncols);
        }

        return *this;
    }


    // Apply 3x3 kernel
    Image applyKernel(int kernel[3][3])
    {
        // Result will be smaller by 2 rows and 2 columns
        int resultRows = nrows - 2;
        int resultCols = ncols - 2;

        Image result(resultRows, resultCols);

        for(int i = 0; i < resultRows; i++)
        {
            for(int j = 0; j < resultCols; j++)
            {
                int sum = 0;

                // Apply 3x3 kernel
                for(int ki = 0; ki < 3; ki++)
                {
                    for(int kj = 0; kj < 3; kj++)
                    {
                        sum = sum +
                              imageData[i + ki][j + kj]
                              * kernel[ki][kj];
                    }
                }

                result(i, j) = sum;
            }
        }

        return result;
    }
};


int main()
{
    int rows;
    int columns;

    cout << "Enter number of rows and columns: ";
    cin >> rows >> columns;

    // Create image
    Image img(rows, columns);

    // Fill image
    cout << "\nEnter image values:\n";
    img.fillImage();

    // Display original image
    cout << "\nOriginal Image:\n";
    img.display();

    // Test copy constructor
    Image img2 = img;

    cout << "\nCopied Image:\n";
    img2.display();

    // 3x3 kernel
    int kernel[3][3] =
    {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    // Apply kernel
    Image result = img.applyKernel(kernel);

    cout << "\nResult after applying 3x3 kernel:\n";
    result.display();

    // Test operator()
    cout << "\nElement at (1,1): ";
    cout << img(1,1) << endl;

    return 0;
}
