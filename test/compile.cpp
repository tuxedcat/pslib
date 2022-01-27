#include "core/base.h"

#include "dp/cht.h"
#include "dp/dnc.h"
#include "dp/knuth.h"
#include "dp/slope.h"
#include "dp/sparse.h"

#include "geom/line.h"
#include "geom/polygon.h"
#include "geom/rect.h"
#include "geom/vec2.h"

#include "graph/bipartite.h"
#include "graph/flow.h"
#include "graph/UD.h"
#include "graph/UU.h"
#include "graph/WD.h"
#include "graph/WU.h"

#include "math/linalg/mat.h"
#include "math/linalg/matGF2.h"
#include "math/linalg/matdyn.h"
#include "math/linalg/linrec.h"
#include "math/linalg/xorbasis.h"
#include "math/numth/basic.h"
#include "math/numth/advance.h"
#include "math/numth/sieve.h"
#include "math/fft.h"
#include "math/frac.h"
#include "math/lp.h"
#include "math/mod.h"
#include "math/monoid.h"

#include "misc/bucket.h"
#include "misc/bucketbias.h"
#include "misc/cumulQ.h"
#include "misc/debug.h"
#include "misc/fastio.h"
#include "misc/gccext.h"
#include "misc/hashval.h"
#include "misc/heapset.h"
#include "misc/i128.h"
#include "misc/interval.h"
#include "misc/list.h"
#include "misc/mo.h"
#include "misc/monoQ.h"
#include "misc/random.h"
#include "misc/uf.h"
#include "misc/util.h"
#include "misc/zip.h"

#include "str/ahocorasik.h"
#include "str/manacher.h"
#include "str/match.h"
#include "str/sufarr.h"

#include "tree/seg/segdyn.h"
#include "tree/seg/fenwick.h"
#include "tree/hld.h"
#include "tree/linkcut.h"
#include "tree/seg/segpersi.h"
#include "tree/seg/segpersilazy.h"
#include "tree/seg/seg.h"
#include "tree/seg/seg2d.h"
#include "tree/seg/seglazy.h"
#include "tree/toptree.h"
#include "tree/bbst/treap.h"
#include "tree/bbst/treapBST.h"
#include "tree/trie.h"
#include "tree/tree.h"

signed main() {}
