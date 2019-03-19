import {
    StyleSheet
} from 'react-native';

export default styles = StyleSheet.create({
    blackLine: {
        backgroundColor: '#9E9E9E',
        height: 1,
        marginTop: 8,
        marginBottom: 8
    },
    title: {
        fontSize: 32,
        textAlign: 'center',
        color: 'cornflowerblue',
        marginTop: 40,
        marginBottom: 40
    },
    container: {
        flex: 1,
        marginRight: 16,
        marginLeft: 16,
        marginTop: 40,
        marginBottom: 40
    },
    itemContainer: {
        borderBottomWidth: 1,
        borderBottomColor: "lightgrey",
    },
    label: {
        fontSize: 16
    },
    rightLabel: {
        flex: 1,
        fontSize: 16,
        textAlign: 'right'
    },
    highlightLabel: {
        flex: 1,
        fontSize: 16,
        color: '#000000'
    },
    highlightRightLabel: {
        flex: 1,
        fontSize: 16,
        color: '#000000',
        textAlign: 'right'
    },
    billInput: {
        flex: 2
    },
    segmentedControlTab: {
        marginTop: 24,
        marginBottom: 24
    },
    modalOuterContainer: {
        flex: 1,
        justifyContent: "center",
        padding: 16,
        backgroundColor: 'rgba(0,0,0,0.5)' //Translucent
    },
    modalInnerContainer: {
        borderRadius: 8,
        padding: 24,
        backgroundColor: '#ffffff',
    },
    flexLabel: {
        flex: 1,
        fontSize: 16
    },
    slider: {
        flex: 1
    }
});