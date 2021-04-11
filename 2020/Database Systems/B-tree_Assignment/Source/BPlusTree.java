import java.util.ArrayList;
import java.util.List;

public class BPlusTree {
    LeafNode root;
    int degree;
    NonLeafNode nonLeafRoot;
    int nonLeafHeight;

    public BPlusTree() {
        this.root = null;
        this.degree = 0;
        this.nonLeafRoot = null;
        this.nonLeafHeight = 0;
    }

    public BPlusTree(int degree) {
        this.root = null;
        this.degree = degree;
        this.nonLeafRoot = null;
        this.nonLeafHeight = 0;
    }

    class Node {
        int m;
        List<Pair> p;
        Node r;
        NonLeafNode parent;

        public Node() {
            this.m = 0;
            this.p = null;
            this.r = null;
            parent = null;
        }
    }

    class LeafNode extends Node {
        public LeafNode() { super(); }

    }

    class NonLeafNode extends Node {
        public NonLeafNode() { super(); }

    }

    static class Pair {
        int key;

        public Pair() {}

        public Pair(int key) {
            this.key = key;
        }
    }

    static class KeyPair extends Pair {
        int value;

        public KeyPair() {}

        public KeyPair(int key, int value) {
            super(key);
            this.value = value;
        }
    }

    class NodePair extends Pair {
        int key;
        Node child;
    }

    void insertion(KeyPair pair) {
        if(root == null) {
            root = new LeafNode();
            root.p = new ArrayList<>();
            root.m++;
            root.p.add(pair);

        } else {

            LeafNode findNode = findLocation(pair.key);

            if(pair.key < findNode.p.get(0).key) {
                findNode.p.add(0, pair);
                findNode.m++;

            } else if(pair.key > findNode.p.get(findNode.m - 1).key) {
                findNode.p.add(findNode.m, pair);
                findNode.m++;

            } else {
                for (int i = 0; i < findNode.m; i++) {

                    if (pair.key > findNode.p.get(i).key && pair.key < findNode.p.get(i + 1).key) {
                        findNode.p.add(i + 1, pair);
                        findNode.m++;

                        break;
                    }

                }
            }

            //split
            if(findNode.m >= degree) {
                int split = 0;
                List<Pair> splitPairs = new ArrayList<>();

                for(int i = (degree / 2); i < findNode.m; i++) {

                    splitPairs.add(findNode.p.get(degree / 2));
                    findNode.p.remove(degree / 2);
                    split++;
                }

                LeafNode tmpNode = new LeafNode();
                tmpNode.p = splitPairs;
                tmpNode.m = split;
                tmpNode.r = findNode.r;

                findNode.m = findNode.m - split;
                findNode.r = tmpNode;

                insertNonLeafNode(findNode, tmpNode);

            }
        }
    }

    void insertNonLeafNode(LeafNode findNode, LeafNode tmpNode) {
        if(nonLeafRoot == null) {
            nonLeafRoot = new NonLeafNode();
            NodePair nodePair = new NodePair();
            nodePair.child = findNode;
            nodePair.key = tmpNode.p.get(0).key;

            nonLeafRoot.p = new ArrayList<>();
            nonLeafRoot.r = new Node();

            nonLeafRoot.p.add(nodePair);
            nonLeafRoot.m++;
            nonLeafRoot.r = tmpNode;

            findNode.parent = nonLeafRoot;
            tmpNode.parent = nonLeafRoot;

            nonLeafHeight++;

        } else {
            int insertKey = tmpNode.p.get(0).key;

            NonLeafNode nonLeafNode = findNonLeafLocation(insertKey);

            NodePair nodePair = new NodePair();
            nodePair.child = findNode;
            nodePair.key = insertKey;

            tmpNode.parent = nonLeafNode;

            if(((NodePair)nonLeafNode.p.get(0)).key > insertKey) {
                nonLeafNode.p.add(0, nodePair);
                nonLeafNode.m++;

            } else if(((NodePair) nonLeafNode.p.get(nonLeafNode.m - 1)).key < insertKey) {
                nonLeafNode.p.add(nonLeafNode.m, nodePair);

                nonLeafNode.m++;


            } else {
                for (int i = 0; i < nonLeafNode.m; i++) {
                    if(insertKey > ((NodePair)nonLeafNode.p.get(i)).key && insertKey < ((NodePair) nonLeafNode.p.get(i + 1)).key) {
                        nonLeafNode.p.add(i + 1, nodePair);
                        nonLeafNode.m++;
                        break;
                    }
                }


            }

//            printNonLeafNode(nonLeafRoot);

            //split
            // 다시 봐야돼
            if(nonLeafNode.m >= degree) {
                int middle = degree / 2;
                int left = 0;
                int right = 0;
                NonLeafNode newLeft = new NonLeafNode();
                newLeft.p = new ArrayList<>();
                NonLeafNode newRight = new NonLeafNode();
                newRight.p = new ArrayList<>();

                //parent가 null이면 현재노드를 루트노드로 올리고 나머지를 다시 설정해 줘야함
                while(nonLeafNode.m >= degree) {
                    if(nonLeafNode.parent == null) {
//                        System.out.println("//Tester");
//                        for(int i = 0; i < nonLeafNode.m; i++) {
//                            System.out.println(nonLeafNode.p.get(i).key);
//                        }
                        for(int i = 0; i < middle; i++) {
                            newLeft.p.add(nonLeafNode.p.get(0));
                            ((NodePair) nonLeafNode.p.get(0)).child.parent = newLeft;
                            nonLeafNode.p.remove(0);
                            nonLeafNode.m--;
                            left++;
                        }
                        newLeft.r = ((NodePair) nonLeafNode.p.get(0)).child;
                        ((NodePair) nonLeafNode.p.get(0)).child.parent = newLeft;
                        newLeft.m = left;

                        for(int i = 1; i < middle + 1; i++) {
                            newRight.p.add(nonLeafNode.p.get(1));
                            ((NodePair) nonLeafNode.p.get(0)).child.parent = newRight;
                            nonLeafNode.p.remove(1);
                            nonLeafNode.m--;
                            right++;
                        }


                        newRight.r = nonLeafNode.r;
                        nonLeafNode.r.parent = newRight;
                        newRight.m = right;

                        ((NodePair) nonLeafNode.p.get(0)).child = newLeft;
                        nonLeafNode.r = newRight;
                        nonLeafHeight++;

                        newLeft.parent = nonLeafNode;
                        newRight.parent = nonLeafNode;

//                        printNonLeafNode(nonLeafRoot);
                        break;
                    } else {
                        NonLeafNode parentNode = nonLeafNode.parent;
                        for (int i = 0; i < middle; i++) {
                            newLeft.p.add(nonLeafNode.p.get(0));
                            ((NodePair) nonLeafNode.p.get(0)).child.parent = newLeft;
                            nonLeafNode.p.remove(0);
                            nonLeafNode.m--;
                            left++;
                        }
                        newLeft.r = ((NodePair) nonLeafNode.p.get(0)).child;
                        ((NodePair) nonLeafNode.p.get(0)).child.parent = newLeft;
                        newLeft.m = left;

                        for (int i = middle + 1; i < degree; i++) {
                            newRight.p.add(nonLeafNode.p.get(middle + 1));
                            ((NodePair) nonLeafNode.p.get(0)).child.parent = newRight;
                            nonLeafNode.p.remove(middle + 1);
                            nonLeafNode.m--;
                            right++;
                        }

                        newRight.r = nonLeafNode.r;
                        nonLeafNode.r.parent = newRight;
                        newRight.m = right;

                        ((NodePair) nonLeafNode.p.get(0)).child = newLeft;

                        if (parentNode.p.get(0).key > nonLeafNode.p.get(0).key) {
                            parentNode.p.add(0, nonLeafNode.p.get(0));
                            parentNode.m++;
                        } else if (parentNode.p.get(parentNode.m - 1).key < nonLeafNode.p.get(0).key) {
                            parentNode.p.add(nonLeafNode.p.get(0));
                            parentNode.m++;
                        }


                        newLeft.parent = parentNode;
                        newRight.parent = parentNode;

//                        printNonLeafNode(nonLeafRoot);

                        nonLeafNode = nonLeafNode.parent;
                    }
                }
            }
        }
    }



    void deletion(int key) {
        if (root == null)
            System.out.println("NO TREE!!!");
        else {
            LeafNode leafNode = findDeleteLocation(key);

            if (leafNode == null) {
                System.out.println("Not Found");
            } else {
                for (int i = 0; i < leafNode.m; i++) {
                    if (key == leafNode.p.get(i).key) {
                        leafNode.p.remove(i);
                        leafNode.m--;

                        if (leafNode.parent != null) {
                            for (int j = 0; j < leafNode.parent.m; j++) {
                                if (key == ((NodePair) leafNode.parent.p.get(i)).key) {
                                    ((NodePair) leafNode.parent.p.get(j)).key = leafNode.p.get(0).key;
                                    break;
                                }
                            }
                        }

                    }
                }

                if (leafNode.m == 0) {
                    LeafNode previous = findPrevious(leafNode);
                    previous.r = leafNode.r;

                    for (int i = 0; i < leafNode.parent.m; i++) {
                        if (key == ((NodePair) leafNode.parent.p.get(i)).key) {
                            leafNode.parent.p.remove(i);
                            leafNode.parent.m--;
                            break;
                        }
                    }

                } else if (leafNode.m < degree / 2) {
                    if (leafNode.r == null) {
                        LeafNode leftNode = findPrevious(leafNode);
                        if (leftNode.m < degree && leafNode.m > degree / 2) {
                            leafNode.p.add(0, leftNode.p.get(leftNode.m));
                            leftNode.m--;
                            leafNode.m++;

                            ((NodePair) leafNode.parent.p.get(leafNode.m - 1)).key = leafNode.p.get(0).key;
                        } else {
                            int oldKey = leafNode.p.get(0).key;

                            for (int i = 0; i < leafNode.m; i++) {
                                leftNode.p.add(leafNode.p.get(0));
                                leafNode.p.remove(0);
                                leafNode.m--;
                                leftNode.m++;
                            }

                            for (int i = 0; i < leafNode.parent.m; i++) {
                                if (((NodePair) leafNode.parent.p.get(i)).key == oldKey) {
                                    leafNode.parent.p.remove(i);
                                    leafNode.parent.m--;
                                    break;
                                }
                            }
                        }
                    } else if (findPrevious(leafNode) == null) {
                        if (leafNode.r.m < degree && leafNode.r.m > degree / 2) {
                            //Borrow

                            leafNode.p.add(leafNode.r.p.get(0));
                            leafNode.m++;
                            leafNode.r.p.remove(0);
                            leafNode.r.m--;

                            if (leafNode.parent == leafNode.r.parent) {
                                for (int i = 0; i < leafNode.parent.m; i++) {
                                    if (((NodePair) leafNode.parent.p.get(i)).key == key) {
                                        ((NodePair) leafNode.parent.p.get(i)).key = leafNode.r.p.get(0).key;
                                    }
                                }
                            }
                        } else {
                            for (int i = 0; i < leafNode.m; i++) {
                                leafNode.p.add(leafNode.r.p.get(i));
                                leafNode.r.p.remove(0);
                                leafNode.m++;
                                leafNode.r = leafNode.r.r;
                            }

                            for (int i = 0; i < leafNode.parent.m; i++) {
                                if (((NodePair) leafNode.parent.p.get(i)).key == key) {
                                    leafNode.parent.p.remove(i);
                                    leafNode.parent.m--;

                                }
                            }
                        }
                    } else {
                        if (leafNode.r.m < degree && leafNode.r.m > degree / 2) {

                            leafNode.p.add(leafNode.r.p.get(0));
                            leafNode.m++;
                            leafNode.r.p.remove(0);
                            leafNode.r.m--;

                            if (leafNode.parent == leafNode.r.parent) {
                                for (int i = 0; i < leafNode.parent.m; i++) {
                                    if (((NodePair) leafNode.parent.p.get(i)).key == key) {
                                        ((NodePair) leafNode.parent.p.get(i)).key = leafNode.r.p.get(0).key;
                                    }
                                }
                            }
                        } else {
                            //Merge with siblling which has same parent
                            int oldKey = leafNode.r.p.get(0).key;

                            if (leafNode.parent == leafNode.r.parent) {
                                //right merge
                                for (int i = 0; i < leafNode.m; i++) {
                                    leafNode.r.p.add(i, leafNode.p.get(0));
                                    leafNode.p.remove(0);

                                    leafNode.m--;
                                    leafNode.r.m++;

                                }

                                for (int i = 0; i < leafNode.parent.m; i++) {
                                    if (((NodePair) leafNode.parent.p.get(i)).key == oldKey) {
                                        leafNode.parent.p.remove(i);
                                        leafNode.parent.m--;
                                        break;
                                    }
                                }

                            } else {
                                //left merge
                                LeafNode leftNode = findPrevious(leafNode);

                                int oldKey1 = leafNode.p.get(0).key;

                                for (int i = 0; i < leafNode.m; i++) {
                                    leftNode.p.add(leafNode.p.get(0));
                                    leafNode.p.remove(0);
                                    leafNode.m--;
                                    leftNode.m++;
                                }

                                for (int i = 0; i < leafNode.parent.m; i++) {
                                    if (((NodePair) leafNode.parent.p.get(i)).key == oldKey1) {
                                        leafNode.parent.p.remove(i);
                                        leafNode.parent.m--;
                                        break;
                                    }
                                }
                            }

                        }
                    }
                }
            }
        }
    }




    void singleSearch(int key) {
        LeafNode findNode = root;

        if(key < findNode.p.get(0).key) {
            System.out.println("NOT FOUND");
            return;
        }

        while(findNode.r != null) {
            for(int i = 0; i < findNode.m; i++) {
                if(key >= findNode.p.get(0).key && key <= findNode.p.get(findNode.m - 1).key) {
                    System.out.println();

                    if (key == findNode.p.get(i).key) {
                        System.out.println(key +"의 value: " + ((KeyPair) findNode.p.get(i)).value);
                        return;
                    }
                    System.out.println(findNode.p.get(i).key + ", " + ((KeyPair) findNode.p.get(i)).value);
                }

                System.out.print(findNode.p.get(i).key + " ");
            }


            findNode = (LeafNode) findNode.r;
        }


        System.out.println();
        System.out.println("NOT FOUND");
        return;
    }

    void rangeSearch(int start, int end) {
        LeafNode findNode = root;

        while(findNode.r != null) {
            for(int i = 0; i < findNode.m; i++) {
                if(start <= findNode.p.get(i).key && end >= findNode.p.get(i).key) {
                    System.out.println(findNode.p.get(i).key + ", " + ((KeyPair) findNode.p.get(i)).value);
                }
            }
            findNode = (LeafNode) findNode.r;
        }

    }

    LeafNode findLocation(int key) {
        LeafNode findNode = root;

        if(key < findNode.p.get(0).key) {
            return findNode;
        }

        while(findNode.r != null) {
            if(key > findNode.p.get(0).key && key < findNode.r.p.get(0).key)
                break;

            findNode = (LeafNode) findNode.r;
        }

        return findNode;
    }

    NonLeafNode findNonLeafLocation(int key) {
        NonLeafNode findNode = nonLeafRoot;

        if(nonLeafHeight == 1) {
            return findNode;
        } else {
            for(int i = 0; i < nonLeafHeight - 1; i++) {
                if(findNode.p.get(0).key > key) {
                    findNode = (NonLeafNode) ((NodePair)findNode.p.get(0)).child;
                } else {
                    findNode = (NonLeafNode) (findNode.r);
                }
            }

            return findNode;
        }
    }

    LeafNode findDeleteLocation(int key) {
        LeafNode findNode = root;

        if(key < findNode.p.get(0).key) {
            return null;
        }

        while(findNode.r != null) {
            for(int i = 0; i < findNode.m; i++) {
                if(key >= findNode.p.get(0).key && key <= findNode.p.get(findNode.m - 1).key) {
                    if (key == findNode.p.get(i).key) {
//                        System.out.println(((KeyPair) findNode.p.get(i)).value);
                        return findNode;
                    }
                }
            }

            findNode = (LeafNode) findNode.r;
        }

        return null;
    }

    void printNonLeafNode(NonLeafNode nonLeafNode) {
        for(int j = 0; j < nonLeafNode.m; j++) {
            System.out.print(((NodePair)nonLeafNode.p.get(j)).key);
        }
        System.out.println();

        if(nonLeafNode.r instanceof LeafNode)
            return;

        printNonLeafNode ((NonLeafNode) ((NodePair) nonLeafNode.p.get(0)).child);

        printNonLeafNode(((NonLeafNode) nonLeafNode.r));

    }

    LeafNode findPrevious(LeafNode leafNode) {
        LeafNode findNode = root;
        if(findNode == leafNode) {
            return findNode;
        }
        while(findNode.r != leafNode) {
            findNode = (LeafNode) findNode.r;
        }

        return findNode;
    }

    NonLeafNode balanceNonLeaf (NonLeafNode nonLeafNode) {
        if(nonLeafNode.m < degree && nonLeafNode != nonLeafRoot) {
            return nonLeafNode;
        }

        if(nonLeafNode.r instanceof LeafNode)
            return null;

        balanceNonLeaf((NonLeafNode) ((NodePair) nonLeafNode.p.get(0)).child);

        balanceNonLeaf(((NonLeafNode) nonLeafNode.r));

        return null;
    }
}
