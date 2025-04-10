#pragma once
#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;
struct Node {

    int weight{};
    char ch{};
    Node* left  = nullptr;
    Node* right = nullptr;
};

class HaffmanTree {
private:
    vector< Node* > nodes;

    void clean_up( Node* node ) {
        if ( node->left == nullptr ) {
            delete node;
            return;
        }
        clean_up( node->left );
        clean_up( node->right );
        delete node;
    }

    void traverse( Node* node, map< char, string >& code_map, string code ) {
        if ( node->left == nullptr ) {
            code_map[ node->ch ] = code;
            return;
        }
        traverse( node->left, code_map, code + "0" );
        traverse( node->right, code_map, code + "1" );
    }

public:
    HaffmanTree() = default;

    ~HaffmanTree() {
        clean_up( nodes[ 0 ] );
    }

    void add_node( int w, char c ) {
        nodes.push_back( new Node( w, c ) );
    }

    void get_code_map( map< char, string >& code_map ) {
        traverse( nodes[ 0 ], code_map, "" );
    }

    void build() {
        sort( nodes.begin(), nodes.end(), []( Node* n1, Node* n2 ) { return n1->weight < n2->weight; } );
        while ( nodes.size() > 1 ) {
            auto min1       = nodes[ 0 ];
            auto min2       = nodes[ 1 ];
            auto new_node   = new Node( min1->weight + min2->weight );
            new_node->left  = min1;
            new_node->right = min2;
            if ( new_node->weight >= nodes.back()->weight ) {
                nodes.push_back( new_node );
            }
            else {
                for ( auto it = nodes.begin(); it != nodes.end(); ++it ) {
                    if ( new_node->weight < ( *it )->weight ) {
                        nodes.insert( it, new_node );
                        break;
                    }
                }
            }
            // erase
            nodes.erase( nodes.begin() );
            nodes.erase( nodes.begin() );
        }
    }
};
