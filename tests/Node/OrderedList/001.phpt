--TEST--
CommonMark\Node\OrderedList
--FILE--
<?php
$list = new CommonMark\Node\OrderedList();

var_dump($list->tight, $list->delimiter, $list->start);

$list = new CommonMark\Node\OrderedList(true);

var_dump($list->tight, $list->delimiter, $list->start);

$list = new CommonMark\Node\OrderedList(true, CommonMark\Node\Lists\Delimit\Period);

var_dump($list->tight, $list->delimiter, $list->start);

$list = new CommonMark\Node\OrderedList(true, CommonMark\Node\Lists\Delimit\Paren);

var_dump($list->tight, $list->delimiter, $list->start);

$list = new CommonMark\Node\OrderedList(true, CommonMark\Node\Lists\Delimit\Paren, 3);

var_dump($list->tight, $list->delimiter, $list->start);

try {
	$list = new CommonMark\Node\OrderedList(1);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
bool(false)
int(0)
int(0)
bool(true)
int(0)
int(0)
bool(true)
int(1)
int(0)
bool(true)
int(2)
int(0)
bool(true)
int(2)
int(3)
OK
