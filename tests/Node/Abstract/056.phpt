--TEST--
CommonMark\Node isset startColumn
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

$title = $doc->firstChild;

$f = function() use($title) {
	return isset($title->startColumn);
};

if ($f() && $f() == $f()) {
	echo "OK";
}
?>
--EXPECT--
OK
