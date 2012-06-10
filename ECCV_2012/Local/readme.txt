Specification of some data structures

1. a deformation basis struct, which has the following fields:

    - K:        The Lie algebraic dimension
    - siz:      The image size, in form of [h w]
    - Bx:       The x-components [N x K]
    - By:       The y-components [N x K]

  Here, N = h * w is the number of pixels per image.

2. a neighborhood system

    - ns:       the number of seeds
    - np:       the number of pairs
    - siz:      the image size
    - seeds:    the list of all seed indices [1 x ns]
    - smap:     the seed indices of all pairs [1 x np]
    - nbs:      the list of neighbors of all seeds [1 x ns cell arrray]
    - s:        the list of the source indices of all pairs [1 x np]
    - t:        the list of the target indices of all pairs [1 x np]
    - w:        the list of the weights of all pairs [1 x np]
    - X:        the matrix of pixel vectors [N x n]
    - Gx:       the matrix of x-gradient vectors [N x ns]
    - Gy:       the matrix of y-gradient vectors [N x ns]

