--TEST--
CommonMark\Node isset startLine
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

$title = $doc->firstChild;

$f = function() use($title) {
	return isset($title->startLine);
};

if ($f() && $f() == $f()) {
	echo "OK";
}
?>
--EXPECT--
OK
