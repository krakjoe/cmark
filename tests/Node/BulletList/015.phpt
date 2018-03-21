--TEST--
CommonMark\Node\BulletList isset delimiter
--FILE--
<?php
$list = new CommonMark\Node\BulletList;

var_dump($list->delimiter);
var_dump(isset($list->delimiter));

$list->delimiter = CommonMark\Node\Lists\Delimit\Period;

var_dump($list->delimiter);
var_dump(isset($list->delimiter));
?>
--EXPECT--
int(0)
bool(true)
int(1)
bool(true)
