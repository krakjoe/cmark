--TEST--
CommonMark\Node\BulletList
--FILE--
<?php
$list = new CommonMark\Node\BulletList();

var_dump($list->tight, $list->delimiter);

$list = new CommonMark\Node\BulletList(true);

var_dump($list->tight, $list->delimiter);

$list = new CommonMark\Node\BulletList(true, CommonMark\Node\Lists\Delimit\Period);

var_dump($list->tight, $list->delimiter);

$list = new CommonMark\Node\BulletList(true, CommonMark\Node\Lists\Delimit\Paren);

var_dump($list->tight, $list->delimiter);

try {
	$list = new CommonMark\Node\BulletList(1);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
bool(false)
int(0)
bool(true)
int(0)
bool(true)
int(1)
bool(true)
int(2)
OK
