--TEST--
CommonMark\Node cached read next
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====

Hello World
EOD
);

$f = function() use($doc) {
	return $doc->firstChild->next;
};

$f();
$f();
echo "OK";
?>
--EXPECT--
OK
