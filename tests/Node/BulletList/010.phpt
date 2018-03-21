--TEST--
CommonMark\Node\BulletList cached read delim
--FILE--
<?php
$list = new CommonMark\Node\BulletList(true, CommonMark\Node\Lists\Delimit\Period);

$f = function() use($list) {
	return $list->delimiter;
};

var_dump($f());

$list->delimiter = CommonMark\Node\Lists\Delimit\Paren;

var_dump($f());
?>
--EXPECT--
int(1)
int(2)
